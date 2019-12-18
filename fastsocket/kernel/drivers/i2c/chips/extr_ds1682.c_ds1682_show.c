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
typedef  int /*<<< orphan*/  u8 ;
struct sensor_device_attribute_2 {int nr; int /*<<< orphan*/  index; } ;
struct i2c_client {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct device_attribute {TYPE_1__ attr; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  scalar_t__ __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ) ; 
 int i2c_smbus_read_i2c_block_data (struct i2c_client*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ le32_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  sprintf (char*,char*,long) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 
 struct sensor_device_attribute_2* to_sensor_dev_attr_2 (struct device_attribute*) ; 

__attribute__((used)) static ssize_t ds1682_show(struct device *dev, struct device_attribute *attr,
			   char *buf)
{
	struct sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);
	struct i2c_client *client = to_i2c_client(dev);
	__le32 val = 0;
	int rc;

	dev_dbg(dev, "ds1682_show() called on %s\n", attr->attr.name);

	/* Read the register */
	rc = i2c_smbus_read_i2c_block_data(client, sattr->index, sattr->nr,
					   (u8 *) & val);
	if (rc < 0)
		return -EIO;

	/* Special case: the 32 bit regs are time values with 1/4s
	 * resolution, scale them up to milliseconds */
	if (sattr->nr == 4)
		return sprintf(buf, "%llu\n",
			((unsigned long long)le32_to_cpu(val)) * 250);

	/* Format the output string and return # of bytes */
	return sprintf(buf, "%li\n", (long)le32_to_cpu(val));
}