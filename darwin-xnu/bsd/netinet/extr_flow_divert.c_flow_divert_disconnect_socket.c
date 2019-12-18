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
struct inpcb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PF_INET6 ; 
 scalar_t__ SOCK_CHECK_DOM (struct socket*,int /*<<< orphan*/ ) ; 
 scalar_t__ SOCK_DGRAM ; 
 scalar_t__ SOCK_TYPE (struct socket*) ; 
 int /*<<< orphan*/  in6_pcbdetach (struct inpcb*) ; 
 int /*<<< orphan*/  in_pcbdetach (struct inpcb*) ; 
 int /*<<< orphan*/  soisdisconnected (struct socket*) ; 
 struct inpcb* sotoinpcb (struct socket*) ; 

__attribute__((used)) static void
flow_divert_disconnect_socket(struct socket *so)
{
	soisdisconnected(so);
	if (SOCK_TYPE(so) == SOCK_DGRAM) {
		struct inpcb *inp = NULL;

		inp = sotoinpcb(so);
		if (inp != NULL) {
#if INET6
			if (SOCK_CHECK_DOM(so, PF_INET6))
				in6_pcbdetach(inp);
			else
#endif /* INET6 */
				in_pcbdetach(inp);
		}
	}
}