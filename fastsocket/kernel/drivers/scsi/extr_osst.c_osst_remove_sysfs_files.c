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
struct device_driver {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  driver_attr_version ; 
 int /*<<< orphan*/  driver_remove_file (struct device_driver*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void osst_remove_sysfs_files(struct device_driver *sysfs)
{
	driver_remove_file(sysfs, &driver_attr_version);
}