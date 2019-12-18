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
struct msghdr {int msg_namelen; int msg_flags; struct sockaddr* msg_name; } ;
struct kvec {scalar_t__ iov_len; int /*<<< orphan*/  iov_base; } ;

/* Variables and functions */
 int MSG_MORE ; 
 int XS_SENDMSG_FLAGS ; 
 int kernel_sendmsg (struct socket*,struct msghdr*,struct kvec*,int,scalar_t__) ; 

__attribute__((used)) static int xs_send_kvec(struct socket *sock, struct sockaddr *addr, int addrlen, struct kvec *vec, unsigned int base, int more)
{
	struct msghdr msg = {
		.msg_name	= addr,
		.msg_namelen	= addrlen,
		.msg_flags	= XS_SENDMSG_FLAGS | (more ? MSG_MORE : 0),
	};
	struct kvec iov = {
		.iov_base	= vec->iov_base + base,
		.iov_len	= vec->iov_len - base,
	};

	if (iov.iov_len != 0)
		return kernel_sendmsg(sock, &msg, &iov, 1, iov.iov_len);
	return kernel_sendmsg(sock, &msg, NULL, 0, 0);
}