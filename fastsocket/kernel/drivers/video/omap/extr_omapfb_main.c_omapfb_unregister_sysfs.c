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
struct omapfb_device {TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  ctrl_attr_grp ; 
 int /*<<< orphan*/  dev_attr_caps_num ; 
 int /*<<< orphan*/  dev_attr_caps_text ; 
 int /*<<< orphan*/  device_remove_file (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panel_attr_grp ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void omapfb_unregister_sysfs(struct omapfb_device *fbdev)
{
	sysfs_remove_group(&fbdev->dev->kobj, &ctrl_attr_grp);
	sysfs_remove_group(&fbdev->dev->kobj, &panel_attr_grp);
	device_remove_file(fbdev->dev, &dev_attr_caps_num);
	device_remove_file(fbdev->dev, &dev_attr_caps_text);
}