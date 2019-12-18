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
struct msghdr {int msg_flags; } ;
struct kvec {void* iov_base; unsigned int iov_len; } ;

/* Variables and functions */
 int MSG_DONTWAIT ; 
 int MSG_NOSIGNAL ; 
 int kernel_sendmsg (struct socket*,struct msghdr*,struct kvec*,int,unsigned int) ; 

__attribute__((used)) static int rds_tcp_sendmsg(struct socket *sock, void *data, unsigned int len)
{
	struct kvec vec = {
                .iov_base = data,
                .iov_len = len,
	};
        struct msghdr msg = {
                .msg_flags = MSG_DONTWAIT | MSG_NOSIGNAL,
        };

	return kernel_sendmsg(sock, &msg, &vec, 1, vec.iov_len);
}