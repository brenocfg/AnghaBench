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
struct inpcb {int inp_vflag; } ;

/* Variables and functions */
 int EINVAL ; 
 int INP_IPV4 ; 
 int in6_getpeeraddr (struct socket*,struct sockaddr**) ; 
 int in6_sin_2_v4mapsin6_in_sock (struct sockaddr**) ; 
 int in_getpeeraddr (struct socket*,struct sockaddr**) ; 
 struct inpcb* sotoinpcb (struct socket*) ; 

int
in6_mapped_peeraddr(struct socket *so, struct sockaddr **nam)
{
	struct	inpcb *inp = sotoinpcb(so);
	int	error;

	if (inp == NULL)
		return (EINVAL);
	if (inp->inp_vflag & INP_IPV4) {
		error = in_getpeeraddr(so, nam);
		if (error == 0)
			error = in6_sin_2_v4mapsin6_in_sock(nam);
	} else {
		/* scope issues will be handled in in6_getpeeraddr(). */
		error = in6_getpeeraddr(so, nam);
	}
	return (error);
}