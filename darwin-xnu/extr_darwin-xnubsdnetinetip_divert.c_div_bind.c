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
struct socket {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; } ;
struct sockaddr {scalar_t__ sa_family; } ;
struct proc {int dummy; } ;
struct inpcb {int dummy; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int EAFNOSUPPORT ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 int in_pcbbind (struct inpcb*,struct sockaddr*,struct proc*) ; 
 struct inpcb* sotoinpcb (struct socket*) ; 

__attribute__((used)) static int
div_bind(struct socket *so, struct sockaddr *nam, struct proc *p)
{
	struct inpcb *inp;
	int error;

	inp = sotoinpcb(so);
	/* in_pcbbind assumes that the socket is a sockaddr_in
	* and in_pcbbind requires a valid address. Since divert
	* sockets don't we need to make sure the address is
	* filled in properly.
	* XXX -- divert should not be abusing in_pcbind
	* and should probably have its own family.
	*/
	if (nam->sa_family != AF_INET) {
		error = EAFNOSUPPORT;
	} else {
               ((struct sockaddr_in *)(void *)nam)->sin_addr.s_addr = INADDR_ANY;
		error = in_pcbbind(inp, nam, p);
	}
	return error;
}