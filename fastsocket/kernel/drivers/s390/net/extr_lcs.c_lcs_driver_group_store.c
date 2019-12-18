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
 int ccwgroup_create_from_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char const*) ; 
 int /*<<< orphan*/  lcs_ccw_driver ; 
 TYPE_1__ lcs_group_driver ; 
 int /*<<< orphan*/  lcs_root_dev ; 

__attribute__((used)) static ssize_t
lcs_driver_group_store(struct device_driver *ddrv, const char *buf,
		       size_t count)
{
	int err;
	err = ccwgroup_create_from_string(lcs_root_dev,
					  lcs_group_driver.driver_id,
					  &lcs_ccw_driver, 2, buf);
	return err ? err : count;
}