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
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; } ;
struct sockaddr_in {int dummy; } ;
struct sockaddr {int dummy; } ;
struct proc {int dummy; } ;
struct inpcb {int inp_flags; int /*<<< orphan*/  inp_vflag; } ;

/* Variables and functions */
 int EINVAL ; 
 int IN6P_IPV6_V6ONLY ; 
 scalar_t__ IN6_IS_ADDR_UNSPECIFIED (int /*<<< orphan*/ *) ; 
 scalar_t__ IN6_IS_ADDR_V4MAPPED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INP_IPV4 ; 
 int /*<<< orphan*/  INP_IPV6 ; 
 int in6_pcbbind (struct inpcb*,struct sockaddr*,struct proc*) ; 
 int /*<<< orphan*/  in6_sin6_2_sin (struct sockaddr_in*,struct sockaddr_in6*) ; 
 int in_pcbbind (struct inpcb*,struct sockaddr*,struct proc*) ; 
 struct inpcb* sotoinpcb (struct socket*) ; 

__attribute__((used)) static int
udp6_bind(struct socket *so, struct sockaddr *nam, struct proc *p)
{
	struct inpcb *inp;
	int error;

	inp = sotoinpcb(so);
	if (inp == NULL)
		return (EINVAL);

	inp->inp_vflag &= ~INP_IPV4;
	inp->inp_vflag |= INP_IPV6;
	if ((inp->inp_flags & IN6P_IPV6_V6ONLY) == 0) {
		struct sockaddr_in6 *sin6_p;

		sin6_p = (struct sockaddr_in6 *)(void *)nam;

		if (IN6_IS_ADDR_UNSPECIFIED(&sin6_p->sin6_addr)) {
			inp->inp_vflag |= INP_IPV4;
		} else if (IN6_IS_ADDR_V4MAPPED(&sin6_p->sin6_addr)) {
			struct sockaddr_in sin;

			in6_sin6_2_sin(&sin, sin6_p);
			inp->inp_vflag |= INP_IPV4;
			inp->inp_vflag &= ~INP_IPV6;
			error = in_pcbbind(inp, (struct sockaddr *)&sin, p);
			return (error);
		}
	}

	error = in6_pcbbind(inp, nam, p);
	return (error);
}