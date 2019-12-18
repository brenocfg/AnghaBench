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
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int (* get_current_limit ) (struct regulator_dev*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct regulator_dev*) ; 

__attribute__((used)) static int _regulator_get_current_limit(struct regulator_dev *rdev)
{
	int ret;

	mutex_lock(&rdev->mutex);

	/* sanity check */
	if (!rdev->desc->ops->get_current_limit) {
		ret = -EINVAL;
		goto out;
	}

	ret = rdev->desc->ops->get_current_limit(rdev);
out:
	mutex_unlock(&rdev->mutex);
	return ret;
}