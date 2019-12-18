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
struct raw3215_info {struct raw3215_info* buffer; } ;
struct ccw_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ccw_device_set_offline (struct ccw_device*) ; 
 struct raw3215_info* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct raw3215_info*) ; 

__attribute__((used)) static void raw3215_remove (struct ccw_device *cdev)
{
	struct raw3215_info *raw;

	ccw_device_set_offline(cdev);
	raw = dev_get_drvdata(&cdev->dev);
	if (raw) {
		dev_set_drvdata(&cdev->dev, NULL);
		kfree(raw->buffer);
		kfree(raw);
	}
}