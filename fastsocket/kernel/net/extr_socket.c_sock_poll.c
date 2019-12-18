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
struct file {struct socket* private_data; } ;
typedef  int /*<<< orphan*/  poll_table ;
struct TYPE_2__ {unsigned int (* poll ) (struct file*,struct socket*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 unsigned int stub1 (struct file*,struct socket*,int /*<<< orphan*/ *) ; 

unsigned int sock_poll(struct file *file, poll_table *wait)
{
	struct socket *sock;

	/*
	 *      We can't return errors to poll, so it's either yes or no.
	 */
	sock = file->private_data;
	return sock->ops->poll(file, sock, wait);
}