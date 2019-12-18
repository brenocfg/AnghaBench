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
struct platform_device {int /*<<< orphan*/  resource; } ;
struct device {int /*<<< orphan*/  platform_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 struct platform_device* to_platform_device (struct device*) ; 

__attribute__((used)) static void gigaset_device_release(struct device *dev)
{
	struct platform_device *pdev = to_platform_device(dev);

	/* adapted from platform_device_release() in drivers/base/platform.c */
	//FIXME is this actually necessary?
	kfree(dev->platform_data);
	kfree(pdev->resource);
}