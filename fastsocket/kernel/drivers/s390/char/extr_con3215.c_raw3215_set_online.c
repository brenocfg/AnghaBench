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
struct raw3215_info {int dummy; } ;
struct ccw_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 struct raw3215_info* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int raw3215_startup (struct raw3215_info*) ; 

__attribute__((used)) static int raw3215_set_online (struct ccw_device *cdev)
{
	struct raw3215_info *raw;

	raw = dev_get_drvdata(&cdev->dev);
	if (!raw)
		return -ENODEV;

	return raw3215_startup(raw);
}