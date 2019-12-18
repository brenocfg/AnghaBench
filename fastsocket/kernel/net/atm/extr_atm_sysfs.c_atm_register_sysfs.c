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
struct device {int /*<<< orphan*/ * class; } ;
struct atm_dev {int /*<<< orphan*/  number; int /*<<< orphan*/  type; struct device class_dev; } ;

/* Variables and functions */
 scalar_t__* atm_attrs ; 
 int /*<<< orphan*/  atm_class ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct atm_dev*) ; 
 int /*<<< orphan*/  dev_set_name (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int device_create_file (struct device*,scalar_t__) ; 
 int /*<<< orphan*/  device_del (struct device*) ; 
 int device_register (struct device*) ; 
 int /*<<< orphan*/  device_remove_file (struct device*,scalar_t__) ; 

int atm_register_sysfs(struct atm_dev *adev)
{
	struct device *cdev = &adev->class_dev;
	int i, j, err;

	cdev->class = &atm_class;
	dev_set_drvdata(cdev, adev);

	dev_set_name(cdev, "%s%d", adev->type, adev->number);
	err = device_register(cdev);
	if (err < 0)
		return err;

	for (i = 0; atm_attrs[i]; i++) {
		err = device_create_file(cdev, atm_attrs[i]);
		if (err)
			goto err_out;
	}

	return 0;

err_out:
	for (j = 0; j < i; j++)
		device_remove_file(cdev, atm_attrs[j]);
	device_del(cdev);
	return err;
}