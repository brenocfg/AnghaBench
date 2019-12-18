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
struct file_info {int /*<<< orphan*/  reqlists_lock; int /*<<< orphan*/  req_complete; int /*<<< orphan*/  wait_complete; } ;
struct file {struct file_info* private_data; } ;
typedef  int /*<<< orphan*/  poll_table ;

/* Variables and functions */
 unsigned int POLLIN ; 
 unsigned int POLLOUT ; 
 unsigned int POLLRDNORM ; 
 unsigned int POLLWRNORM ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static unsigned int raw1394_poll(struct file *file, poll_table * pt)
{
	struct file_info *fi = file->private_data;
	unsigned int mask = POLLOUT | POLLWRNORM;
	unsigned long flags;

	poll_wait(file, &fi->wait_complete, pt);

	spin_lock_irqsave(&fi->reqlists_lock, flags);
	if (!list_empty(&fi->req_complete)) {
		mask |= POLLIN | POLLRDNORM;
	}
	spin_unlock_irqrestore(&fi->reqlists_lock, flags);

	return mask;
}