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
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct rtc_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_attr_wakealarm ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int device_create_file (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtc_does_wakealarm (struct rtc_device*) ; 

void rtc_sysfs_add_device(struct rtc_device *rtc)
{
	int err;

	/* not all RTCs support both alarms and wakeup */
	if (!rtc_does_wakealarm(rtc))
		return;

	err = device_create_file(&rtc->dev, &dev_attr_wakealarm);
	if (err)
		dev_err(rtc->dev.parent,
			"failed to create alarm attribute, %d\n", err);
}