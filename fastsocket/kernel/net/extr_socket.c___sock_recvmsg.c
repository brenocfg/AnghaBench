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
struct msghdr {int dummy; } ;
struct kiocb {int dummy; } ;

/* Variables and functions */
 int __sock_recvmsg_nosec (struct kiocb*,struct socket*,struct msghdr*,size_t,int) ; 
 int security_socket_recvmsg (struct socket*,struct msghdr*,size_t,int) ; 

__attribute__((used)) static inline int __sock_recvmsg(struct kiocb *iocb, struct socket *sock,
				 struct msghdr *msg, size_t size, int flags)
{
	int err = security_socket_recvmsg(sock, msg, size, flags);

	return err ?: __sock_recvmsg_nosec(iocb, sock, msg, size, flags);
}