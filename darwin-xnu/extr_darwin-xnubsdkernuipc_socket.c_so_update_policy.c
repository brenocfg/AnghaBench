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

/* Variables and functions */
 scalar_t__ PF_INET ; 
 scalar_t__ PF_INET6 ; 
 scalar_t__ SOCK_DOM (struct socket*) ; 
 int /*<<< orphan*/  inp_update_policy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sotoinpcb (struct socket*) ; 

void
so_update_policy(struct socket *so)
{
	if (SOCK_DOM(so) == PF_INET || SOCK_DOM(so) == PF_INET6)
		(void) inp_update_policy(sotoinpcb(so));
}