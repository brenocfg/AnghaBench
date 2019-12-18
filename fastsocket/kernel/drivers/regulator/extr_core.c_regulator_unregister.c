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
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;
struct regulator_dev {TYPE_1__ dev; scalar_t__ supply; int /*<<< orphan*/  list; int /*<<< orphan*/  open_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_unregister (TYPE_1__*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regulator_list_mutex ; 
 int /*<<< orphan*/  sysfs_remove_link (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  unset_regulator_supplies (struct regulator_dev*) ; 

void regulator_unregister(struct regulator_dev *rdev)
{
	if (rdev == NULL)
		return;

	mutex_lock(&regulator_list_mutex);
	WARN_ON(rdev->open_count);
	unset_regulator_supplies(rdev);
	list_del(&rdev->list);
	if (rdev->supply)
		sysfs_remove_link(&rdev->dev.kobj, "supply");
	device_unregister(&rdev->dev);
	mutex_unlock(&regulator_list_mutex);
}