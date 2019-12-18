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
struct module {int dummy; } ;
struct device {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int sysfs_schedule_callback (int /*<<< orphan*/ *,void (*) (void*),struct device*,struct module*) ; 

int device_schedule_callback_owner(struct device *dev,
		void (*func)(struct device *), struct module *owner)
{
	return sysfs_schedule_callback(&dev->kobj,
			(void (*)(void *)) func, dev, owner);
}