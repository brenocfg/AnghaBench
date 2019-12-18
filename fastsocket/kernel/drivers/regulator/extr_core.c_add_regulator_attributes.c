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
struct regulator_ops {scalar_t__ set_suspend_mode; scalar_t__ set_suspend_voltage; scalar_t__ set_suspend_disable; scalar_t__ set_suspend_enable; scalar_t__ set_current_limit; scalar_t__ set_voltage; scalar_t__ get_status; scalar_t__ is_enabled; scalar_t__ get_mode; scalar_t__ get_current_limit; scalar_t__ get_voltage; } ;
struct device {int dummy; } ;
struct regulator_dev {int /*<<< orphan*/  constraints; TYPE_1__* desc; struct device dev; } ;
struct TYPE_2__ {scalar_t__ type; struct regulator_ops* ops; } ;

/* Variables and functions */
 scalar_t__ REGULATOR_CURRENT ; 
 int /*<<< orphan*/  dev_attr_max_microamps ; 
 int /*<<< orphan*/  dev_attr_max_microvolts ; 
 int /*<<< orphan*/  dev_attr_microamps ; 
 int /*<<< orphan*/  dev_attr_microvolts ; 
 int /*<<< orphan*/  dev_attr_min_microamps ; 
 int /*<<< orphan*/  dev_attr_min_microvolts ; 
 int /*<<< orphan*/  dev_attr_opmode ; 
 int /*<<< orphan*/  dev_attr_requested_microamps ; 
 int /*<<< orphan*/  dev_attr_state ; 
 int /*<<< orphan*/  dev_attr_status ; 
 int /*<<< orphan*/  dev_attr_suspend_disk_microvolts ; 
 int /*<<< orphan*/  dev_attr_suspend_disk_mode ; 
 int /*<<< orphan*/  dev_attr_suspend_disk_state ; 
 int /*<<< orphan*/  dev_attr_suspend_mem_microvolts ; 
 int /*<<< orphan*/  dev_attr_suspend_mem_mode ; 
 int /*<<< orphan*/  dev_attr_suspend_mem_state ; 
 int /*<<< orphan*/  dev_attr_suspend_standby_microvolts ; 
 int /*<<< orphan*/  dev_attr_suspend_standby_mode ; 
 int /*<<< orphan*/  dev_attr_suspend_standby_state ; 
 int device_create_file (struct device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int add_regulator_attributes(struct regulator_dev *rdev)
{
	struct device		*dev = &rdev->dev;
	struct regulator_ops	*ops = rdev->desc->ops;
	int			status = 0;

	/* some attributes need specific methods to be displayed */
	if (ops->get_voltage) {
		status = device_create_file(dev, &dev_attr_microvolts);
		if (status < 0)
			return status;
	}
	if (ops->get_current_limit) {
		status = device_create_file(dev, &dev_attr_microamps);
		if (status < 0)
			return status;
	}
	if (ops->get_mode) {
		status = device_create_file(dev, &dev_attr_opmode);
		if (status < 0)
			return status;
	}
	if (ops->is_enabled) {
		status = device_create_file(dev, &dev_attr_state);
		if (status < 0)
			return status;
	}
	if (ops->get_status) {
		status = device_create_file(dev, &dev_attr_status);
		if (status < 0)
			return status;
	}

	/* some attributes are type-specific */
	if (rdev->desc->type == REGULATOR_CURRENT) {
		status = device_create_file(dev, &dev_attr_requested_microamps);
		if (status < 0)
			return status;
	}

	/* all the other attributes exist to support constraints;
	 * don't show them if there are no constraints, or if the
	 * relevant supporting methods are missing.
	 */
	if (!rdev->constraints)
		return status;

	/* constraints need specific supporting methods */
	if (ops->set_voltage) {
		status = device_create_file(dev, &dev_attr_min_microvolts);
		if (status < 0)
			return status;
		status = device_create_file(dev, &dev_attr_max_microvolts);
		if (status < 0)
			return status;
	}
	if (ops->set_current_limit) {
		status = device_create_file(dev, &dev_attr_min_microamps);
		if (status < 0)
			return status;
		status = device_create_file(dev, &dev_attr_max_microamps);
		if (status < 0)
			return status;
	}

	/* suspend mode constraints need multiple supporting methods */
	if (!(ops->set_suspend_enable && ops->set_suspend_disable))
		return status;

	status = device_create_file(dev, &dev_attr_suspend_standby_state);
	if (status < 0)
		return status;
	status = device_create_file(dev, &dev_attr_suspend_mem_state);
	if (status < 0)
		return status;
	status = device_create_file(dev, &dev_attr_suspend_disk_state);
	if (status < 0)
		return status;

	if (ops->set_suspend_voltage) {
		status = device_create_file(dev,
				&dev_attr_suspend_standby_microvolts);
		if (status < 0)
			return status;
		status = device_create_file(dev,
				&dev_attr_suspend_mem_microvolts);
		if (status < 0)
			return status;
		status = device_create_file(dev,
				&dev_attr_suspend_disk_microvolts);
		if (status < 0)
			return status;
	}

	if (ops->set_suspend_mode) {
		status = device_create_file(dev,
				&dev_attr_suspend_standby_mode);
		if (status < 0)
			return status;
		status = device_create_file(dev,
				&dev_attr_suspend_mem_mode);
		if (status < 0)
			return status;
		status = device_create_file(dev,
				&dev_attr_suspend_disk_mode);
		if (status < 0)
			return status;
	}

	return status;
}