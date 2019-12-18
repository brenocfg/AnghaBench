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
struct page {int dummy; } ;
struct TYPE_2__ {int (* sendpage ) (struct socket*,struct page*,int,size_t,int) ;} ;

/* Variables and functions */
 int sock_no_sendpage (struct socket*,struct page*,int,size_t,int) ; 
 int /*<<< orphan*/  sock_update_classid (int /*<<< orphan*/ ) ; 
 int stub1 (struct socket*,struct page*,int,size_t,int) ; 

int kernel_sendpage(struct socket *sock, struct page *page, int offset,
		    size_t size, int flags)
{
	sock_update_classid(sock->sk);

	if (sock->ops->sendpage)
		return sock->ops->sendpage(sock, page, offset, size, flags);

	return sock_no_sendpage(sock, page, offset, size, flags);
}