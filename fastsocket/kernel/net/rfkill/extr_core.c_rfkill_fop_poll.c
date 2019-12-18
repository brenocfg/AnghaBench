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
struct rfkill_data {int /*<<< orphan*/  mtx; int /*<<< orphan*/  events; int /*<<< orphan*/  read_wait; } ;
struct file {struct rfkill_data* private_data; } ;
typedef  int /*<<< orphan*/  poll_table ;

/* Variables and functions */
 unsigned int POLLIN ; 
 unsigned int POLLOUT ; 
 unsigned int POLLRDNORM ; 
 unsigned int POLLWRNORM ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned int rfkill_fop_poll(struct file *file, poll_table *wait)
{
	struct rfkill_data *data = file->private_data;
	unsigned int res = POLLOUT | POLLWRNORM;

	poll_wait(file, &data->read_wait, wait);

	mutex_lock(&data->mtx);
	if (!list_empty(&data->events))
		res = POLLIN | POLLRDNORM;
	mutex_unlock(&data->mtx);

	return res;
}