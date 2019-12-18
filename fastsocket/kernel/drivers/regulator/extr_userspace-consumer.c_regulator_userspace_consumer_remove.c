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
struct userspace_consumer_data {int /*<<< orphan*/  supplies; int /*<<< orphan*/  num_supplies; scalar_t__ enabled; } ;
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  attr_group ; 
 int /*<<< orphan*/  kfree (struct userspace_consumer_data*) ; 
 struct userspace_consumer_data* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_bulk_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int regulator_userspace_consumer_remove(struct platform_device *pdev)
{
	struct userspace_consumer_data *data = platform_get_drvdata(pdev);

	sysfs_remove_group(&pdev->dev.kobj, &attr_group);

	if (data->enabled)
		regulator_bulk_disable(data->num_supplies, data->supplies);

	regulator_bulk_free(data->num_supplies, data->supplies);
	kfree(data);

	return 0;
}