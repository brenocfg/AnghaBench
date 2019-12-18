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
struct i2c_dev {struct i2c_dev* dev; } ;
struct i2c_adapter {int /*<<< orphan*/  nr; int /*<<< orphan*/  name; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_MAJOR ; 
 scalar_t__ IS_ERR (struct i2c_dev*) ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PTR_ERR (struct i2c_dev*) ; 
 int /*<<< orphan*/  dev_attr_name ; 
 struct i2c_dev* device_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int device_create_file (struct i2c_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct i2c_dev* get_free_i2c_dev (struct i2c_adapter*) ; 
 int /*<<< orphan*/  i2c_dev_class ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  return_i2c_dev (struct i2c_dev*) ; 

__attribute__((used)) static int i2cdev_attach_adapter(struct i2c_adapter *adap)
{
	struct i2c_dev *i2c_dev;
	int res;

	i2c_dev = get_free_i2c_dev(adap);
	if (IS_ERR(i2c_dev))
		return PTR_ERR(i2c_dev);

	/* register this i2c device with the driver core */
	i2c_dev->dev = device_create(i2c_dev_class, &adap->dev,
				     MKDEV(I2C_MAJOR, adap->nr), NULL,
				     "i2c-%d", adap->nr);
	if (IS_ERR(i2c_dev->dev)) {
		res = PTR_ERR(i2c_dev->dev);
		goto error;
	}
	res = device_create_file(i2c_dev->dev, &dev_attr_name);
	if (res)
		goto error_destroy;

	pr_debug("i2c-dev: adapter [%s] registered as minor %d\n",
		 adap->name, adap->nr);
	return 0;
error_destroy:
	device_destroy(i2c_dev_class, MKDEV(I2C_MAJOR, adap->nr));
error:
	return_i2c_dev(i2c_dev);
	return res;
}