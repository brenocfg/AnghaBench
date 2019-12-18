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
typedef  int ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  driver_id; } ;

/* Variables and functions */
 TYPE_1__ qeth_core_ccwgroup_driver ; 
 int qeth_core_driver_group (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qeth_core_root_dev ; 

__attribute__((used)) static ssize_t
qeth_core_driver_group_store(struct device_driver *ddrv, const char *buf,
			   size_t count)
{
	int err;
	err = qeth_core_driver_group(buf, qeth_core_root_dev,
					qeth_core_ccwgroup_driver.driver_id);
	if (err)
		return err;
	else
		return count;
}