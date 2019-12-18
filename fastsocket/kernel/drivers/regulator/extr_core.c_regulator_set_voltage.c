#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct regulator_dev {int /*<<< orphan*/  mutex; TYPE_2__* desc; } ;
struct regulator {int min_uV; int max_uV; struct regulator_dev* rdev; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int (* set_voltage ) (struct regulator_dev*,int,int) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  REGULATOR_EVENT_VOLTAGE_CHANGE ; 
 int /*<<< orphan*/  _notifier_call_chain (struct regulator_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int regulator_check_voltage (struct regulator_dev*,int*,int*) ; 
 int stub1 (struct regulator_dev*,int,int) ; 

int regulator_set_voltage(struct regulator *regulator, int min_uV, int max_uV)
{
	struct regulator_dev *rdev = regulator->rdev;
	int ret;

	mutex_lock(&rdev->mutex);

	/* sanity check */
	if (!rdev->desc->ops->set_voltage) {
		ret = -EINVAL;
		goto out;
	}

	/* constraints check */
	ret = regulator_check_voltage(rdev, &min_uV, &max_uV);
	if (ret < 0)
		goto out;
	regulator->min_uV = min_uV;
	regulator->max_uV = max_uV;
	ret = rdev->desc->ops->set_voltage(rdev, min_uV, max_uV);

out:
	_notifier_call_chain(rdev, REGULATOR_EVENT_VOLTAGE_CHANGE, NULL);
	mutex_unlock(&rdev->mutex);
	return ret;
}