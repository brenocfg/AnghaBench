#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct socket {int so_state; scalar_t__ so_pcb; } ;
struct in_addr {int dummy; } ;
struct in6_addr {int dummy; } ;
struct inpcb {int inp_vflag; TYPE_1__* inp_socket; struct in_addr inp_faddr; struct in_addr inp_laddr; struct in6_addr in6p_faddr; struct in6_addr in6p_laddr; int /*<<< orphan*/  inp_fport; int /*<<< orphan*/  inp_lport; } ;
typedef  int pid_t ;
struct TYPE_2__ {int last_pid; } ;

/* Variables and functions */
 int EHOSTUNREACH ; 
 int ENOTCONN ; 
 int INP_IPV4 ; 
 int INP_IPV6 ; 
 int SS_ISCONNECTED ; 
 int /*<<< orphan*/  WNT_RELEASE ; 
 struct inpcb* in6_pcblookup_hash (int /*<<< orphan*/ *,struct in6_addr*,int /*<<< orphan*/ ,struct in6_addr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  in_pcb_checkstate (struct inpcb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct inpcb* in_pcblookup_hash (int /*<<< orphan*/ *,struct in_addr,int /*<<< orphan*/ ,struct in_addr,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  socket_lock (struct socket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_unlock (struct socket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcbinfo ; 

__attribute__((used)) static int
tcp_lookup_peer_pid_locked(struct socket *so, pid_t *out_pid)
{
	int error = EHOSTUNREACH;
	*out_pid = -1;
	if ((so->so_state & SS_ISCONNECTED) == 0) return ENOTCONN;

	struct inpcb	*inp = (struct inpcb*)so->so_pcb;
	uint16_t		lport = inp->inp_lport;
	uint16_t		fport = inp->inp_fport;
	struct inpcb	*finp = NULL;
	struct  in6_addr laddr6, faddr6;
	struct in_addr laddr4, faddr4;

	if (inp->inp_vflag & INP_IPV6) {
		laddr6 = inp->in6p_laddr;
		faddr6 = inp->in6p_faddr;
	} else if (inp->inp_vflag & INP_IPV4) {
		laddr4 = inp->inp_laddr;
		faddr4 = inp->inp_faddr;
	}

	socket_unlock(so, 0);
	if (inp->inp_vflag & INP_IPV6) {
		finp = in6_pcblookup_hash(&tcbinfo, &laddr6, lport, &faddr6, fport, 0, NULL);
	} else if (inp->inp_vflag & INP_IPV4) {
		finp = in_pcblookup_hash(&tcbinfo, laddr4, lport, faddr4, fport, 0, NULL);
	}

	if (finp) {
		*out_pid = finp->inp_socket->last_pid;
		error = 0;
		in_pcb_checkstate(finp, WNT_RELEASE, 0);
	}
	socket_lock(so, 0);

	return error;
}