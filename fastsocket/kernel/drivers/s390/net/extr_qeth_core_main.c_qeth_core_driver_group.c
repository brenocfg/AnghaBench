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
struct device {int dummy; } ;

/* Variables and functions */
 int ccwgroup_create_from_string (struct device*,unsigned long,int /*<<< orphan*/ *,int,char const*) ; 
 int /*<<< orphan*/  qeth_ccw_driver ; 

__attribute__((used)) static int qeth_core_driver_group(const char *buf, struct device *root_dev,
				unsigned long driver_id)
{
	return ccwgroup_create_from_string(root_dev, driver_id,
					   &qeth_ccw_driver, 3, buf);
}