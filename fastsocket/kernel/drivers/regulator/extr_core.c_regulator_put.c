#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  kobj; } ;
struct regulator_dev {int /*<<< orphan*/  owner; scalar_t__ exclusive; int /*<<< orphan*/  open_count; TYPE_1__ dev; } ;
struct TYPE_5__ {struct regulator* name; } ;
struct TYPE_6__ {TYPE_2__ attr; } ;
struct regulator {int /*<<< orphan*/  list; TYPE_3__ dev_attr; scalar_t__ dev; struct regulator* supply_name; struct regulator_dev* rdev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct regulator*) ; 
 int /*<<< orphan*/  device_remove_file (scalar_t__,TYPE_3__*) ; 
 int /*<<< orphan*/  kfree (struct regulator*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regulator_list_mutex ; 
 int /*<<< orphan*/  sysfs_remove_link (int /*<<< orphan*/ *,struct regulator*) ; 

void regulator_put(struct regulator *regulator)
{
	struct regulator_dev *rdev;

	if (regulator == NULL || IS_ERR(regulator))
		return;

	mutex_lock(&regulator_list_mutex);
	rdev = regulator->rdev;

	/* remove any sysfs entries */
	if (regulator->dev) {
		sysfs_remove_link(&rdev->dev.kobj, regulator->supply_name);
		kfree(regulator->supply_name);
		device_remove_file(regulator->dev, &regulator->dev_attr);
		kfree(regulator->dev_attr.attr.name);
	}
	list_del(&regulator->list);
	kfree(regulator);

	rdev->open_count--;
	rdev->exclusive = 0;

	module_put(rdev->owner);
	mutex_unlock(&regulator_list_mutex);
}