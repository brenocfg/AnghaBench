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
struct w83791d_data {int /*<<< orphan*/  vrm; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 struct w83791d_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  simple_strtoul (char const*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static ssize_t store_vrm_reg(struct device *dev,
				struct device_attribute *attr,
				const char *buf, size_t count)
{
	struct w83791d_data *data = dev_get_drvdata(dev);

	/* No lock needed as vrm is internal to the driver
	   (not read from a chip register) and so is not
	   updated in w83791d_update_device() */
	data->vrm = simple_strtoul(buf, NULL, 10);

	return count;
}