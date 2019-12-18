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
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;
struct rio_dev {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  rio_config_attr ; 
 int /*<<< orphan*/  sysfs_remove_bin_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void rio_remove_sysfs_dev_files(struct rio_dev *rdev)
{
	sysfs_remove_bin_file(&rdev->dev.kobj, &rio_config_attr);
}