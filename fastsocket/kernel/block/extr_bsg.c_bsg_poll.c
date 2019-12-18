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
struct file {struct bsg_device* private_data; } ;
struct bsg_device {scalar_t__ queued_cmds; scalar_t__ max_queue; int /*<<< orphan*/  lock; int /*<<< orphan*/  done_list; int /*<<< orphan*/  wq_free; int /*<<< orphan*/  wq_done; } ;
typedef  int /*<<< orphan*/  poll_table ;

/* Variables and functions */
 unsigned int POLLIN ; 
 unsigned int POLLOUT ; 
 unsigned int POLLRDNORM ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned int bsg_poll(struct file *file, poll_table *wait)
{
	struct bsg_device *bd = file->private_data;
	unsigned int mask = 0;

	poll_wait(file, &bd->wq_done, wait);
	poll_wait(file, &bd->wq_free, wait);

	spin_lock_irq(&bd->lock);
	if (!list_empty(&bd->done_list))
		mask |= POLLIN | POLLRDNORM;
	if (bd->queued_cmds >= bd->max_queue)
		mask |= POLLOUT;
	spin_unlock_irq(&bd->lock);

	return mask;
}