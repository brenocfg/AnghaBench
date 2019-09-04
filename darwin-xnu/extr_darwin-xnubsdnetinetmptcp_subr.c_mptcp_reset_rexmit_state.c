#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct tcpcb {struct mptsub* t_mpsub; struct inpcb* t_inpcb; } ;
struct socket {int so_flags; } ;
struct mptsub {int /*<<< orphan*/  mpts_flags; } ;
struct inpcb {struct socket* inp_socket; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPTSF_WRITE_STALL ; 
 int SOF_MP_SUBFLOW ; 
 int SOF_MP_TRYFAILOVER ; 

void
mptcp_reset_rexmit_state(struct tcpcb *tp)
{
	struct mptsub *mpts;
	struct inpcb *inp;
	struct socket *so;

	inp = tp->t_inpcb;
	if (inp == NULL)
		return;

	so = inp->inp_socket;
	if (so == NULL)
		return;

	if (!(so->so_flags & SOF_MP_SUBFLOW))
		return;

	mpts = tp->t_mpsub;

	mpts->mpts_flags &= ~MPTSF_WRITE_STALL;
	so->so_flags &= ~SOF_MP_TRYFAILOVER;
}