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
struct msghdr {int msg_iovlen; int /*<<< orphan*/  msg_flags; scalar_t__ msg_controllen; int /*<<< orphan*/ * msg_control; scalar_t__ msg_namelen; int /*<<< orphan*/ * msg_name; struct iovec* msg_iov; } ;
struct kvec {unsigned int iov_len; void* iov_base; } ;
struct iovec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DONTWAIT ; 
 int /*<<< orphan*/  MSG_WAITALL ; 
 int kernel_recvmsg (struct socket*,struct msghdr*,struct kvec*,int,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dst_data_recv_header(struct socket *sock,
		void *data, unsigned int size, int block)
{
	struct msghdr msg;
	struct kvec iov;
	int err;

	iov.iov_base = data;
	iov.iov_len = size;

	msg.msg_iov = (struct iovec *)&iov;
	msg.msg_iovlen = 1;
	msg.msg_name = NULL;
	msg.msg_namelen = 0;
	msg.msg_control = NULL;
	msg.msg_controllen = 0;
	msg.msg_flags = (block)?MSG_WAITALL:MSG_DONTWAIT;

	err = kernel_recvmsg(sock, &msg, &iov, 1, iov.iov_len,
			msg.msg_flags);
	if (err != size)
		return -1;

	return 0;
}