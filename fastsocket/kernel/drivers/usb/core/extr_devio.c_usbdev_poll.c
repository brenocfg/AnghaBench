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
struct poll_table_struct {int dummy; } ;
struct file {int f_mode; struct dev_state* private_data; } ;
struct dev_state {int /*<<< orphan*/  async_completed; int /*<<< orphan*/  wait; } ;

/* Variables and functions */
 int FMODE_WRITE ; 
 unsigned int POLLERR ; 
 unsigned int POLLHUP ; 
 unsigned int POLLOUT ; 
 unsigned int POLLWRNORM ; 
 int /*<<< orphan*/  connected (struct dev_state*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,struct poll_table_struct*) ; 

__attribute__((used)) static unsigned int usbdev_poll(struct file *file,
				struct poll_table_struct *wait)
{
	struct dev_state *ps = file->private_data;
	unsigned int mask = 0;

	poll_wait(file, &ps->wait, wait);
	if (file->f_mode & FMODE_WRITE && !list_empty(&ps->async_completed))
		mask |= POLLOUT | POLLWRNORM;
	if (!connected(ps))
		mask |= POLLERR | POLLHUP;
	return mask;
}