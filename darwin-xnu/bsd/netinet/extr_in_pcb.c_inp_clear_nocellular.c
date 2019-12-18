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
struct socket {int so_restrictions; } ;
struct inpcb {int /*<<< orphan*/  inp_route; int /*<<< orphan*/  inp_flags; struct socket* inp_socket; } ;

/* Variables and functions */
 int /*<<< orphan*/  INP_NO_IFT_CELLULAR ; 
 int /*<<< orphan*/  ROUTE_RELEASE (int /*<<< orphan*/ *) ; 
 int SO_RESTRICT_DENY_CELLULAR ; 

void
inp_clear_nocellular(struct inpcb *inp)
{
	struct socket *so = inp->inp_socket;

	/*
	 * SO_RESTRICT_DENY_CELLULAR socket restriction issued on the socket
	 * has a higher precendence than INP_NO_IFT_CELLULAR.  Clear the flag
	 * if and only if the socket is unrestricted.
	 */
	if (so != NULL && !(so->so_restrictions & SO_RESTRICT_DENY_CELLULAR)) {
		inp->inp_flags &= ~INP_NO_IFT_CELLULAR;

		/* Blow away any cached route in the PCB */
		ROUTE_RELEASE(&inp->inp_route);
	}
}