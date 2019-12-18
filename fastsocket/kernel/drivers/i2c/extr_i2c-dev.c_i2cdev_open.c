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
struct inode {int dummy; } ;
struct i2c_dev {TYPE_1__* adap; } ;
struct i2c_client {struct i2c_adapter* adapter; int /*<<< orphan*/ * driver; int /*<<< orphan*/  name; } ;
struct i2c_adapter {int nr; } ;
struct file {struct i2c_client* private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  nr; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_NAME_SIZE ; 
 struct i2c_dev* i2c_dev_get_by_minor (unsigned int) ; 
 struct i2c_adapter* i2c_get_adapter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_put_adapter (struct i2c_adapter*) ; 
 int /*<<< orphan*/  i2cdev_driver ; 
 unsigned int iminor (struct inode*) ; 
 struct i2c_client* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static int i2cdev_open(struct inode *inode, struct file *file)
{
	unsigned int minor = iminor(inode);
	struct i2c_client *client;
	struct i2c_adapter *adap;
	struct i2c_dev *i2c_dev;
	int ret = 0;

	lock_kernel();
	i2c_dev = i2c_dev_get_by_minor(minor);
	if (!i2c_dev) {
		ret = -ENODEV;
		goto out;
	}

	adap = i2c_get_adapter(i2c_dev->adap->nr);
	if (!adap) {
		ret = -ENODEV;
		goto out;
	}

	/* This creates an anonymous i2c_client, which may later be
	 * pointed to some address using I2C_SLAVE or I2C_SLAVE_FORCE.
	 *
	 * This client is ** NEVER REGISTERED ** with the driver model
	 * or I2C core code!!  It just holds private copies of addressing
	 * information and maybe a PEC flag.
	 */
	client = kzalloc(sizeof(*client), GFP_KERNEL);
	if (!client) {
		i2c_put_adapter(adap);
		ret = -ENOMEM;
		goto out;
	}
	snprintf(client->name, I2C_NAME_SIZE, "i2c-dev %d", adap->nr);
	client->driver = &i2cdev_driver;

	client->adapter = adap;
	file->private_data = client;

out:
	unlock_kernel();
	return ret;
}