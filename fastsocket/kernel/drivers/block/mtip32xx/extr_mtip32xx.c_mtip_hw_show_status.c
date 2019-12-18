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
struct driver_data {int /*<<< orphan*/  dd_flag; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {struct driver_data* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTIP_DDF_OVER_TEMP_BIT ; 
 int /*<<< orphan*/  MTIP_DDF_WRITE_PROTECT_BIT ; 
 TYPE_1__* dev_to_disk (struct device*) ; 
 scalar_t__ sprintf (char*,char*,char*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t mtip_hw_show_status(struct device *dev,
				struct device_attribute *attr,
				char *buf)
{
	struct driver_data *dd = dev_to_disk(dev)->private_data;
	int size = 0;

	if (test_bit(MTIP_DDF_OVER_TEMP_BIT, &dd->dd_flag))
		size += sprintf(buf, "%s", "thermal_shutdown\n");
	else if (test_bit(MTIP_DDF_WRITE_PROTECT_BIT, &dd->dd_flag))
		size += sprintf(buf, "%s", "write_protect\n");
	else
		size += sprintf(buf, "%s", "online\n");

	return size;
}