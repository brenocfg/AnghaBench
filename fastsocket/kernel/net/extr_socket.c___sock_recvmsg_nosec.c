#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct socket {TYPE_1__* ops; int /*<<< orphan*/  sk; } ;
struct sock_iocb {size_t size; int flags; struct msghdr* msg; int /*<<< orphan*/ * scm; struct socket* sock; } ;
struct msghdr {int dummy; } ;
struct kiocb {int dummy; } ;
struct TYPE_2__ {int (* recvmsg ) (struct kiocb*,struct socket*,struct msghdr*,size_t,int) ;} ;

/* Variables and functions */
 struct sock_iocb* kiocb_to_siocb (struct kiocb*) ; 
 int /*<<< orphan*/  sock_update_classid (int /*<<< orphan*/ ) ; 
 int stub1 (struct kiocb*,struct socket*,struct msghdr*,size_t,int) ; 

__attribute__((used)) static inline int __sock_recvmsg_nosec(struct kiocb *iocb, struct socket *sock,
				       struct msghdr *msg, size_t size, int flags)
{
	struct sock_iocb *si = kiocb_to_siocb(iocb);

	sock_update_classid(sock->sk);

	si->sock = sock;
	si->scm = NULL;
	si->msg = msg;
	si->size = size;
	si->flags = flags;

	return sock->ops->recvmsg(iocb, sock, msg, size, flags);
}