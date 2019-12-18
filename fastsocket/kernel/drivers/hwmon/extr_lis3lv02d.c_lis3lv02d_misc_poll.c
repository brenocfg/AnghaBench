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
struct TYPE_2__ {int /*<<< orphan*/  count; int /*<<< orphan*/  misc_wait; } ;

/* Variables and functions */
 unsigned int POLLIN ; 
 unsigned int POLLRDNORM ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 TYPE_1__ lis3_dev ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned int lis3lv02d_misc_poll(struct file *file, poll_table *wait)
{
	poll_wait(file, &lis3_dev.misc_wait, wait);
	if (atomic_read(&lis3_dev.count))
		return POLLIN | POLLRDNORM;
	return 0;
}