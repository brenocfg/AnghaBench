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
struct i2c_client {int /*<<< orphan*/  detected; } ;
struct i2c_board_info {int addr; int /*<<< orphan*/  type; } ;
struct i2c_adapter {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EEXIST ; 
 size_t EINVAL ; 
 int I2C_NAME_SIZE ; 
 int /*<<< orphan*/  core_lock ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,char*,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 struct i2c_client* i2c_new_device (struct i2c_adapter*,struct i2c_board_info*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  memset (struct i2c_board_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sscanf (char*,char*,int*,char*) ; 
 char* strchr (char const*,char) ; 
 struct i2c_adapter* to_i2c_adapter (struct device*) ; 
 int /*<<< orphan*/  userspace_devices ; 

__attribute__((used)) static ssize_t
i2c_sysfs_new_device(struct device *dev, struct device_attribute *attr,
		     const char *buf, size_t count)
{
	struct i2c_adapter *adap = to_i2c_adapter(dev);
	struct i2c_board_info info;
	struct i2c_client *client;
	char *blank, end;
	int res;

	dev_warn(dev, "The new_device interface is still experimental "
		 "and may change in a near future\n");
	memset(&info, 0, sizeof(struct i2c_board_info));

	blank = strchr(buf, ' ');
	if (!blank) {
		dev_err(dev, "%s: Missing parameters\n", "new_device");
		return -EINVAL;
	}
	if (blank - buf > I2C_NAME_SIZE - 1) {
		dev_err(dev, "%s: Invalid device name\n", "new_device");
		return -EINVAL;
	}
	memcpy(info.type, buf, blank - buf);

	/* Parse remaining parameters, reject extra parameters */
	res = sscanf(++blank, "%hi%c", &info.addr, &end);
	if (res < 1) {
		dev_err(dev, "%s: Can't parse I2C address\n", "new_device");
		return -EINVAL;
	}
	if (res > 1  && end != '\n') {
		dev_err(dev, "%s: Extra parameters\n", "new_device");
		return -EINVAL;
	}

	if (info.addr < 0x03 || info.addr > 0x77) {
		dev_err(dev, "%s: Invalid I2C address 0x%hx\n", "new_device",
			info.addr);
		return -EINVAL;
	}

	client = i2c_new_device(adap, &info);
	if (!client)
		return -EEXIST;

	/* Keep track of the added device */
	mutex_lock(&core_lock);
	list_add_tail(&client->detected, &userspace_devices);
	mutex_unlock(&core_lock);
	dev_info(dev, "%s: Instantiated device %s at 0x%02hx\n", "new_device",
		 info.type, info.addr);

	return count;
}