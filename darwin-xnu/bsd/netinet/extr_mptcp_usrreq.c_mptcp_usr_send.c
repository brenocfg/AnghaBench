#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int sb_flags; } ;
struct socket {int so_state; int so_flags1; TYPE_1__ so_snd; } ;
struct sockaddr {int dummy; } ;
struct proc {int dummy; } ;
struct mptses {int dummy; } ;
struct mppcb {scalar_t__ mpp_state; } ;
struct mbuf {scalar_t__ m_len; } ;

/* Variables and functions */
 int ECONNRESET ; 
 int ENOTCONN ; 
 int EOPNOTSUPP ; 
 int EWOULDBLOCK ; 
 scalar_t__ MPPCB_STATE_DEAD ; 
 int PRUS_EOF ; 
 int PRUS_OOB ; 
 int SB_NOCOMPRESS ; 
 int SOF1_PRECONNECT_DATA ; 
 int SS_ISCONNECTED ; 
 int SS_ISCONNECTING ; 
 int SS_NBIO ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 struct mppcb* mpsotomppcb (struct socket*) ; 
 int /*<<< orphan*/  mptcp_insert_dsn (struct mppcb*,struct mbuf*) ; 
 int mptcp_output (struct mptses*) ; 
 struct mptses* mptompte (struct mppcb*) ; 
 int /*<<< orphan*/  sbappendstream (TYPE_1__*,struct mbuf*) ; 
 int sbwait (TYPE_1__*) ; 

__attribute__((used)) static int
mptcp_usr_send(struct socket *mp_so, int prus_flags, struct mbuf *m,
    struct sockaddr *nam, struct mbuf *control, struct proc *p)
{
#pragma unused(nam, p)
	struct mppcb *mpp = mpsotomppcb(mp_so);
	struct mptses *mpte;
	int error = 0;

	if (prus_flags & (PRUS_OOB|PRUS_EOF)) {
		error = EOPNOTSUPP;
		goto out;
	}

	if (nam != NULL) {
		error = EOPNOTSUPP;
		goto out;
	}

	if (control != NULL && control->m_len != 0) {
		error = EOPNOTSUPP;
		goto out;
	}

	if (mpp == NULL || mpp->mpp_state == MPPCB_STATE_DEAD) {
		error = ECONNRESET;
		goto out;
	}
	mpte = mptompte(mpp);
	VERIFY(mpte != NULL);

	if (!(mp_so->so_state & SS_ISCONNECTED) &&
	    !(mp_so->so_flags1 & SOF1_PRECONNECT_DATA)) {
		error = ENOTCONN;
		goto out;
	}

	mptcp_insert_dsn(mpp, m);
	VERIFY(mp_so->so_snd.sb_flags & SB_NOCOMPRESS);
	sbappendstream(&mp_so->so_snd, m);
	m = NULL;

	error = mptcp_output(mpte);
	if (error != 0)
		goto out;

	if (mp_so->so_state & SS_ISCONNECTING) {
		if (mp_so->so_state & SS_NBIO)
			error = EWOULDBLOCK;
		else
			error = sbwait(&mp_so->so_snd);
	}

out:
	if (error) {
		if (m != NULL)
			m_freem(m);
		if (control != NULL)
			m_freem(control);
	}
	return (error);
}