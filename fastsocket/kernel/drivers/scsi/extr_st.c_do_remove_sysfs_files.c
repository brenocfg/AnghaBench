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
struct device_driver {int dummy; } ;
struct TYPE_2__ {struct device_driver gendrv; } ;

/* Variables and functions */
 int /*<<< orphan*/  driver_attr_fixed_buffer_size ; 
 int /*<<< orphan*/  driver_attr_max_sg_segs ; 
 int /*<<< orphan*/  driver_attr_try_direct_io ; 
 int /*<<< orphan*/  driver_attr_version ; 
 int /*<<< orphan*/  driver_remove_file (struct device_driver*,int /*<<< orphan*/ *) ; 
 TYPE_1__ st_template ; 

__attribute__((used)) static void do_remove_sysfs_files(void)
{
	struct device_driver *sysfs = &st_template.gendrv;

	driver_remove_file(sysfs, &driver_attr_version);
	driver_remove_file(sysfs, &driver_attr_max_sg_segs);
	driver_remove_file(sysfs, &driver_attr_fixed_buffer_size);
	driver_remove_file(sysfs, &driver_attr_try_direct_io);
}