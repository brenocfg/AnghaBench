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
struct notifier_block {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 unsigned long BUS_NOTIFY_UNBIND_DRIVER ; 
 int NOTIFY_OK ; 
 int /*<<< orphan*/  ccwgroup_ungroup_callback ; 
 int /*<<< orphan*/  device_schedule_callback (struct device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ccwgroup_notifier(struct notifier_block *nb, unsigned long action,
			     void *data)
{
	struct device *dev = data;

	if (action == BUS_NOTIFY_UNBIND_DRIVER)
		device_schedule_callback(dev, ccwgroup_ungroup_callback);

	return NOTIFY_OK;
}