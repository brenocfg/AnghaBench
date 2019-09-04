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
struct socket {int so_state; } ;
struct inpcb {int dummy; } ;

/* Variables and functions */
 scalar_t__ INP_WAIT_FOR_IF_FEEDBACK (struct inpcb*) ; 
 scalar_t__ PF_INET ; 
 scalar_t__ PF_INET6 ; 
 scalar_t__ SOCK_DOM (struct socket*) ; 
 int SS_ISCONNECTED ; 
 struct inpcb* sotoinpcb (struct socket*) ; 

int
so_wait_for_if_feedback(struct socket *so)
{
	if ((SOCK_DOM(so) == PF_INET || SOCK_DOM(so) == PF_INET6) &&
	    (so->so_state & SS_ISCONNECTED)) {
		struct inpcb *inp = sotoinpcb(so);
		if (INP_WAIT_FOR_IF_FEEDBACK(inp))
			return (1);
	}
	return (0);
}