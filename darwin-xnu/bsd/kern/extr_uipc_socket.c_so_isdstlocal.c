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
struct socket {scalar_t__ so_pcb; } ;
struct inpcb {int /*<<< orphan*/  in6p_faddr; int /*<<< orphan*/  inp_faddr; } ;

/* Variables and functions */
 scalar_t__ PF_INET ; 
 scalar_t__ PF_INET6 ; 
 scalar_t__ SOCK_DOM (struct socket*) ; 
 int in6addr_local (int /*<<< orphan*/ *) ; 
 int inaddr_local (int /*<<< orphan*/ ) ; 

int
so_isdstlocal(struct socket *so) {

	struct inpcb *inp = (struct inpcb *)so->so_pcb;

	if (SOCK_DOM(so) == PF_INET)
		return (inaddr_local(inp->inp_faddr));
	else if (SOCK_DOM(so) == PF_INET6)
		return (in6addr_local(&inp->in6p_faddr));

	return (0);
}