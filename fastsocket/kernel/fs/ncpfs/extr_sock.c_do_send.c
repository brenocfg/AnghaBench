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
struct kvec {int dummy; } ;

/* Variables and functions */
 int kernel_sendmsg (struct socket*,struct msghdr*,struct kvec*,int,int) ; 

__attribute__((used)) static inline int do_send(struct socket *sock, struct kvec *vec, int count,
			  int len, unsigned flags)
{
	struct msghdr msg = { .msg_flags = flags };
	return kernel_sendmsg(sock, &msg, vec, count, len);
}