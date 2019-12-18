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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 int /*<<< orphan*/ * TMP411_TEMP_LOWEST_MSB ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,long) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,long) ; 
 scalar_t__ strict_strtol (char const*,int,long*) ; 
 int /*<<< orphan*/  to_i2c_client (struct device*) ; 

__attribute__((used)) static ssize_t reset_temp_history(struct device *dev,
	struct device_attribute	*devattr, const char *buf, size_t count)
{
	long val;

	if (strict_strtol(buf, 10, &val))
		return -EINVAL;

	if (val != 1) {
		dev_err(dev, "temp_reset_history value %ld not"
			" supported. Use 1 to reset the history!\n", val);
		return -EINVAL;
	}
	i2c_smbus_write_byte_data(to_i2c_client(dev),
		TMP411_TEMP_LOWEST_MSB[0], val);

	return count;
}