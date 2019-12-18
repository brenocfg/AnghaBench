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
struct TYPE_3__ {int /*<<< orphan*/  user; } ;
struct aem_data {int /*<<< orphan*/  id; TYPE_2__* pdev; TYPE_1__ ipmi; int /*<<< orphan*/  hwmon_dev; int /*<<< orphan*/  list; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  aem_idr_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aem_remove_sensors (struct aem_data*) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hwmon_device_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipmi_destroy_user (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct aem_data*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_device_unregister (TYPE_2__*) ; 

__attribute__((used)) static void aem_delete(struct aem_data *data)
{
	list_del(&data->list);
	aem_remove_sensors(data);
	hwmon_device_unregister(data->hwmon_dev);
	ipmi_destroy_user(data->ipmi.user);
	dev_set_drvdata(&data->pdev->dev, NULL);
	platform_device_unregister(data->pdev);
	aem_idr_put(data->id);
	kfree(data);
}