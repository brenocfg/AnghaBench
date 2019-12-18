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
struct page {int dummy; } ;
struct msghdr {int msg_flags; } ;
struct kvec {char* iov_base; size_t iov_len; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  kernel_sendmsg (struct socket*,struct msghdr*,struct kvec*,int,size_t) ; 
 char* kmap (struct page*) ; 
 int /*<<< orphan*/  kunmap (struct page*) ; 

ssize_t sock_no_sendpage(struct socket *sock, struct page *page, int offset, size_t size, int flags)
{
	ssize_t res;
	struct msghdr msg = {.msg_flags = flags};
	struct kvec iov;
	char *kaddr = kmap(page);
	iov.iov_base = kaddr + offset;
	iov.iov_len = size;
	res = kernel_sendmsg(sock, &msg, &iov, 1, size);
	kunmap(page);
	return res;
}