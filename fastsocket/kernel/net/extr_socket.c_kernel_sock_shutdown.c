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
typedef  enum sock_shutdown_cmd { ____Placeholder_sock_shutdown_cmd } sock_shutdown_cmd ;
struct TYPE_2__ {int (* shutdown ) (struct socket*,int) ;} ;

/* Variables and functions */
 int stub1 (struct socket*,int) ; 

int kernel_sock_shutdown(struct socket *sock, enum sock_shutdown_cmd how)
{
	return sock->ops->shutdown(sock, how);
}