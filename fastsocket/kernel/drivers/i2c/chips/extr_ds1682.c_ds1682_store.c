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
typedef  int /*<<< orphan*/  u64 ;
struct sensor_device_attribute_2 {int nr; int /*<<< orphan*/  index; } ;
struct i2c_client {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct device_attribute {TYPE_1__ attr; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 size_t EINVAL ; 
 size_t EIO ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  do_div (int /*<<< orphan*/ ,int) ; 
 int i2c_smbus_write_i2c_block_data (struct i2c_client*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_strtoull (char const*,char**,int /*<<< orphan*/ ) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 
 struct sensor_device_attribute_2* to_sensor_dev_attr_2 (struct device_attribute*) ; 

__attribute__((used)) static ssize_t ds1682_store(struct device *dev, struct device_attribute *attr,
			    const char *buf, size_t count)
{
	struct sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);
	struct i2c_client *client = to_i2c_client(dev);
	char *endp;
	u64 val;
	__le32 val_le;
	int rc;

	dev_dbg(dev, "ds1682_store() called on %s\n", attr->attr.name);

	/* Decode input */
	val = simple_strtoull(buf, &endp, 0);
	if (buf == endp) {
		dev_dbg(dev, "input string not a number\n");
		return -EINVAL;
	}

	/* Special case: the 32 bit regs are time values with 1/4s
	 * resolution, scale input down to quarter-seconds */
	if (sattr->nr == 4)
		do_div(val, 250);

	/* write out the value */
	val_le = cpu_to_le32(val);
	rc = i2c_smbus_write_i2c_block_data(client, sattr->index, sattr->nr,
					    (u8 *) & val_le);
	if (rc < 0) {
		dev_err(dev, "register write failed; reg=0x%x, size=%i\n",
			sattr->index, sattr->nr);
		return -EIO;
	}

	return count;
}