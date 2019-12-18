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
struct socket {scalar_t__ type; } ;
struct msghdr {unsigned long msg_iovlen; int /*<<< orphan*/  msg_flags; struct iovec* msg_iov; scalar_t__ msg_controllen; int /*<<< orphan*/ * msg_control; scalar_t__ msg_namelen; int /*<<< orphan*/ * msg_name; } ;
struct kiocb {int dummy; } ;
struct iovec {scalar_t__ iov_len; } ;
struct file {int f_flags; struct socket* private_data; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DONTWAIT ; 
 int /*<<< orphan*/  MSG_EOR ; 
 int O_NONBLOCK ; 
 scalar_t__ SOCK_SEQPACKET ; 
 int /*<<< orphan*/  __sock_sendmsg (struct kiocb*,struct socket*,struct msghdr*,size_t) ; 

__attribute__((used)) static ssize_t do_sock_write(struct msghdr *msg, struct kiocb *iocb,
			struct file *file, const struct iovec *iov,
			unsigned long nr_segs)
{
	struct socket *sock = file->private_data;
	size_t size = 0;
	int i;

	for (i = 0; i < nr_segs; i++)
		size += iov[i].iov_len;

	msg->msg_name = NULL;
	msg->msg_namelen = 0;
	msg->msg_control = NULL;
	msg->msg_controllen = 0;
	msg->msg_iov = (struct iovec *)iov;
	msg->msg_iovlen = nr_segs;
	msg->msg_flags = (file->f_flags & O_NONBLOCK) ? MSG_DONTWAIT : 0;
	if (sock->type == SOCK_SEQPACKET)
		msg->msg_flags |= MSG_EOR;

	return __sock_sendmsg(iocb, sock, msg, size);
}