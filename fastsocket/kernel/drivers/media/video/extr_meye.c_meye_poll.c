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
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  poll_table ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  doneq; int /*<<< orphan*/  proc_list; } ;

/* Variables and functions */
 unsigned int POLLIN ; 
 unsigned int POLLRDNORM ; 
 scalar_t__ kfifo_len (int /*<<< orphan*/ ) ; 
 TYPE_1__ meye ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned int meye_poll(struct file *file, poll_table *wait)
{
	unsigned int res = 0;

	mutex_lock(&meye.lock);
	poll_wait(file, &meye.proc_list, wait);
	if (kfifo_len(meye.doneq))
		res = POLLIN | POLLRDNORM;
	mutex_unlock(&meye.lock);
	return res;
}