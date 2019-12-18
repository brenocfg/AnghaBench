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
typedef  int /*<<< orphan*/  vhost_work_fn_t ;
struct vhost_poll {unsigned long mask; int /*<<< orphan*/  work; struct vhost_dev* dev; int /*<<< orphan*/  table; int /*<<< orphan*/  wait; } ;
struct vhost_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_poll_funcptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_func_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vhost_poll_func ; 
 int /*<<< orphan*/  vhost_poll_wakeup ; 
 int /*<<< orphan*/  vhost_work_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void vhost_poll_init(struct vhost_poll *poll, vhost_work_fn_t fn,
		     unsigned long mask, struct vhost_dev *dev)
{
	init_waitqueue_func_entry(&poll->wait, vhost_poll_wakeup);
	init_poll_funcptr(&poll->table, vhost_poll_func);
	poll->mask = mask;
	poll->dev = dev;

	vhost_work_init(&poll->work, fn);
}