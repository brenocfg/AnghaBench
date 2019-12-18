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
struct sockaddr_in6 {int sin6_len; int /*<<< orphan*/  sin6_addr; int /*<<< orphan*/  sin6_port; int /*<<< orphan*/  sin6_family; } ;
struct sockaddr_in {int sin_len; int /*<<< orphan*/  sin_addr; int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_family; } ;
union sockaddr_in_4_6 {struct sockaddr_in6 sin6; struct sockaddr_in sin; } ;
struct sockaddr {int dummy; } ;
struct inpcb {int inp_vflag; int /*<<< orphan*/  in6p_laddr; int /*<<< orphan*/  inp_lport; int /*<<< orphan*/  inp_laddr; } ;
typedef  int /*<<< orphan*/  sin46 ;
typedef  int errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 int ENOBUFS ; 
 int INP_IPV4 ; 
 int INP_IPV6 ; 
 int /*<<< orphan*/  bzero (union sockaddr_in_4_6*,int) ; 
 struct sockaddr* dup_sockaddr (struct sockaddr*,int) ; 

__attribute__((used)) static errno_t
flow_divert_inp_to_sockaddr(const struct inpcb *inp, struct sockaddr **local_socket)
{
	int error = 0;
	union sockaddr_in_4_6 sin46;

	bzero(&sin46, sizeof(sin46));
	if (inp->inp_vflag & INP_IPV4) {
		struct sockaddr_in  *sin = &sin46.sin;

		sin->sin_family = AF_INET;
		sin->sin_len = sizeof(*sin);
		sin->sin_port = inp->inp_lport;
		sin->sin_addr = inp->inp_laddr;
	} else if (inp->inp_vflag & INP_IPV6) {
		struct sockaddr_in6 *sin6 = &sin46.sin6;

		sin6->sin6_len = sizeof(*sin6);
		sin6->sin6_family = AF_INET6;
		sin6->sin6_port = inp->inp_lport;
		sin6->sin6_addr = inp->in6p_laddr;
	}
	*local_socket = dup_sockaddr((struct sockaddr *)&sin46, 1);
	if (*local_socket == NULL) {
		error = ENOBUFS;
	}
	return (error);
}