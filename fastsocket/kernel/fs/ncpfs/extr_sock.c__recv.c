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
struct msghdr {int /*<<< orphan*/ * member_0; } ;
struct kvec {void* member_0; int member_1; } ;

/* Variables and functions */
 int kernel_recvmsg (struct socket*,struct msghdr*,struct kvec*,int,int,unsigned int) ; 

__attribute__((used)) static int _recv(struct socket *sock, void *buf, int size, unsigned flags)
{
	struct msghdr msg = {NULL, };
	struct kvec iov = {buf, size};
	return kernel_recvmsg(sock, &msg, &iov, 1, size, flags);
}