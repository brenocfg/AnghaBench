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
struct tcpcb {int dummy; } ;
struct socket {int so_flags; } ;
struct inpcb {int dummy; } ;

/* Variables and functions */
 int SOF_MP_TRYFAILOVER ; 
 int SO_FILT_HINT_LOCKED ; 
 int SO_FILT_HINT_MPFAILOVER ; 
 struct tcpcb* intotcpcb (struct inpcb*) ; 
 int /*<<< orphan*/  soevent (struct socket*,int) ; 
 struct inpcb* sotoinpcb (struct socket*) ; 

void
mptcp_act_on_txfail(struct socket *so)
{
	struct tcpcb *tp = NULL;
	struct inpcb *inp = sotoinpcb(so);

	if (inp == NULL)
		return;

	tp = intotcpcb(inp);
	if (tp == NULL)
		return;

	if (so->so_flags & SOF_MP_TRYFAILOVER)
		return;

	so->so_flags |= SOF_MP_TRYFAILOVER;
	soevent(so, (SO_FILT_HINT_LOCKED | SO_FILT_HINT_MPFAILOVER));
}