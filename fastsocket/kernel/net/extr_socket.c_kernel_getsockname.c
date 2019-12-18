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
struct socket {TYPE_1__* ops; } ;
struct sockaddr {int dummy; } ;
struct TYPE_2__ {int (* getname ) (struct socket*,struct sockaddr*,int*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int stub1 (struct socket*,struct sockaddr*,int*,int /*<<< orphan*/ ) ; 

int kernel_getsockname(struct socket *sock, struct sockaddr *addr,
			 int *addrlen)
{
	return sock->ops->getname(sock, addr, addrlen, 0);
}