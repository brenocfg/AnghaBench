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
struct socket {int dummy; } ;
struct inpcb {int /*<<< orphan*/  inp_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  INP_INADDR_ANY ; 
 int /*<<< orphan*/  socket_lock (struct socket*,int) ; 
 int /*<<< orphan*/  socket_unlock (struct socket*,int) ; 
 struct inpcb* sotoinpcb (struct socket*) ; 

void
inp_clear_INP_INADDR_ANY(struct socket *so)
{
	struct inpcb *inp = NULL;

	socket_lock(so, 1);
	inp = sotoinpcb(so);
	if (inp) {
		inp->inp_flags &= ~INP_INADDR_ANY;
	}
	socket_unlock(so, 1);
}