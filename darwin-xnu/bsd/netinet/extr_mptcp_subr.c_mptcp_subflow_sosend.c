#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct uio {int dummy; } ;
struct socket {int so_flags; int so_state; scalar_t__ last_pid; TYPE_6__* so_proto; } ;
struct sockaddr {int dummy; } ;
struct proc {TYPE_3__* p_stats; } ;
struct TYPE_11__ {int len; int pkt_flags; } ;
struct mbuf {TYPE_4__ m_pkthdr; } ;
struct inpcb {TYPE_1__* inp_last_outifp; } ;
typedef  int /*<<< orphan*/  int64_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_14__ {int /*<<< orphan*/  mpt_mpte; } ;
struct TYPE_13__ {TYPE_5__* pr_usrreqs; } ;
struct TYPE_12__ {int (* pru_send ) (struct socket*,int /*<<< orphan*/ ,struct mbuf*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct proc*) ;} ;
struct TYPE_9__ {int /*<<< orphan*/  ru_msgsnd; } ;
struct TYPE_10__ {TYPE_2__ p_ru; } ;
struct TYPE_8__ {int if_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  DBG_FUNC_END ; 
 int /*<<< orphan*/  DBG_FUNC_START ; 
 scalar_t__ ENTR_SHOULDTRACE ; 
 int EWOULDBLOCK ; 
 scalar_t__ FALSE ; 
 int IFF_LOOPBACK ; 
 int /*<<< orphan*/  KERNEL_ENERGYTRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSIncrementAtomicLong (int /*<<< orphan*/ *) ; 
 int PKTF_MPTCP ; 
 struct proc* PROC_NULL ; 
 scalar_t__ SOCK_CHECK_DOM (struct socket*,int /*<<< orphan*/ ) ; 
 int SOF_CONTENT_FILTER ; 
 int SS_NBIO ; 
 scalar_t__ TRUE ; 
 int UINT16_MAX ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  VM_KERNEL_ADDRPERM (struct socket*) ; 
 struct proc* current_proc () ; 
 int /*<<< orphan*/  inp_update_necp_policy (struct inpcb*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kEnTrActKernSockWrite ; 
 int /*<<< orphan*/  kEnTrFlagNoWork ; 
 int /*<<< orphan*/  kEnTrFlagNonBlocking ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  mptcp_update_last_owner (struct socket*,struct socket*) ; 
 struct socket* mptetoso (int /*<<< orphan*/ ) ; 
 struct proc* proc_find (scalar_t__) ; 
 scalar_t__ proc_pid (struct proc*) ; 
 int /*<<< orphan*/  proc_rele (struct proc*) ; 
 int /*<<< orphan*/  soclearfastopen (struct socket*) ; 
 int sosendcheck (struct socket*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 struct inpcb* sotoinpcb (struct socket*) ; 
 int /*<<< orphan*/  sototcpcb (struct socket*) ; 
 int stub1 (struct socket*,int /*<<< orphan*/ ,struct mbuf*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct proc*) ; 
 TYPE_7__* tptomptp (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mptcp_subflow_sosend(struct socket *so, struct sockaddr *addr, struct uio *uio,
    struct mbuf *top, struct mbuf *control, int flags)
{
	struct socket *mp_so = mptetoso(tptomptp(sototcpcb(so))->mpt_mpte);
	struct proc *p = current_proc();
	boolean_t en_tracing = FALSE, proc_held = FALSE;
	int en_tracing_val;
	int sblocked = 1; /* Pretend as if it is already locked, so we won't relock it */
	int error;

	VERIFY(control == NULL);
	VERIFY(addr == NULL);
	VERIFY(uio == NULL);
	VERIFY(flags == 0);
	VERIFY((so->so_flags & SOF_CONTENT_FILTER) == 0);

	VERIFY(top->m_pkthdr.len > 0 && top->m_pkthdr.len <= UINT16_MAX);
	VERIFY(top->m_pkthdr.pkt_flags & PKTF_MPTCP);

	/*
	 * trace if tracing & network (vs. unix) sockets & and
	 * non-loopback
	 */
	if (ENTR_SHOULDTRACE &&
	    (SOCK_CHECK_DOM(so, AF_INET) || SOCK_CHECK_DOM(so, AF_INET6))) {
		struct inpcb *inp = sotoinpcb(so);
		if (inp->inp_last_outifp != NULL &&
		    !(inp->inp_last_outifp->if_flags & IFF_LOOPBACK)) {
			en_tracing = TRUE;
			en_tracing_val = top->m_pkthdr.len;
			KERNEL_ENERGYTRACE(kEnTrActKernSockWrite, DBG_FUNC_START,
			    VM_KERNEL_ADDRPERM(so),
			    ((so->so_state & SS_NBIO) ? kEnTrFlagNonBlocking : 0),
			    (int64_t)en_tracing_val);
		}
	}

	mptcp_update_last_owner(so, mp_so);

	if (mp_so->last_pid != proc_pid(p)) {
		p = proc_find(mp_so->last_pid);
		if (p == PROC_NULL) {
			p = current_proc();
		} else {
			proc_held = TRUE;
		}
	}

#if NECP
	inp_update_necp_policy(sotoinpcb(so), NULL, NULL, 0);
#endif /* NECP */

	OSIncrementAtomicLong(&p->p_stats->p_ru.ru_msgsnd);

	error = sosendcheck(so, NULL, top->m_pkthdr.len, 0, 1, 0, &sblocked, NULL);
	if (error)
		goto out;

	error = (*so->so_proto->pr_usrreqs->pru_send)(so, 0, top, NULL, NULL, p);
	top = NULL;

out:
	if (top != NULL)
		m_freem(top);

	if (proc_held)
		proc_rele(p);

	soclearfastopen(so);

	if (en_tracing) {
		KERNEL_ENERGYTRACE(kEnTrActKernSockWrite, DBG_FUNC_END,
		    VM_KERNEL_ADDRPERM(so),
		    ((error == EWOULDBLOCK) ? kEnTrFlagNoWork : 0),
		    (int64_t)en_tracing_val);
	}

	return (error);

}