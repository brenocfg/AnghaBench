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
struct msghdr {unsigned int msg_flags; } ;
struct kvec {unsigned char* member_0; int member_1; } ;

/* Variables and functions */
 int MSG_DONTWAIT ; 
 int MSG_NOSIGNAL ; 
 int kernel_recvmsg (struct socket*,struct msghdr*,struct kvec*,int,int,int) ; 

__attribute__((used)) static int
_recvfrom(struct socket *socket, unsigned char *ubuf, int size, unsigned flags)
{
	struct kvec iov = {ubuf, size};
	struct msghdr msg = {.msg_flags = flags};
	msg.msg_flags |= MSG_DONTWAIT | MSG_NOSIGNAL;
	return kernel_recvmsg(socket, &msg, &iov, 1, size, msg.msg_flags);
}