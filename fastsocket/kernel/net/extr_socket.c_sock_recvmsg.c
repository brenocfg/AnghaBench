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
struct sock_iocb {int dummy; } ;
struct msghdr {int dummy; } ;
struct kiocb {struct sock_iocb* private; } ;

/* Variables and functions */
 int EIOCBQUEUED ; 
 int __sock_recvmsg (struct kiocb*,struct socket*,struct msghdr*,size_t,int) ; 
 int /*<<< orphan*/  init_sync_kiocb (struct kiocb*,int /*<<< orphan*/ *) ; 
 int wait_on_sync_kiocb (struct kiocb*) ; 

int sock_recvmsg(struct socket *sock, struct msghdr *msg,
		 size_t size, int flags)
{
	struct kiocb iocb;
	struct sock_iocb siocb;
	int ret;

	init_sync_kiocb(&iocb, NULL);
	iocb.private = &siocb;
	ret = __sock_recvmsg(&iocb, sock, msg, size, flags);
	if (-EIOCBQUEUED == ret)
		ret = wait_on_sync_kiocb(&iocb);
	return ret;
}