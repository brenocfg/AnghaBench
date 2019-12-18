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
struct sockaddr {int dummy; } ;
struct in6_addr {int dummy; } ;
struct inpcb {struct in6_addr in6p_laddr; int /*<<< orphan*/  inp_lport; } ;
typedef  int /*<<< orphan*/  in_port_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOBUFS ; 
 struct sockaddr* in6_sockaddr (int /*<<< orphan*/ ,struct in6_addr*) ; 
 struct inpcb* sotoinpcb (struct socket*) ; 

int
in6_getsockaddr(struct socket *so, struct sockaddr **nam)
{
	struct inpcb *inp;
	struct in6_addr addr;
	in_port_t port;

	if ((inp = sotoinpcb(so)) == NULL)
		return (EINVAL);

	port = inp->inp_lport;
	addr = inp->in6p_laddr;

	*nam = in6_sockaddr(port, &addr);
	if (*nam == NULL)
		return (ENOBUFS);
	return (0);
}