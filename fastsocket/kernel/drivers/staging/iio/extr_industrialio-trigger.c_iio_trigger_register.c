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
struct iio_trigger {int /*<<< orphan*/  dev; int /*<<< orphan*/  list; scalar_t__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_set_name (int /*<<< orphan*/ *,char*,unsigned long) ; 
 int device_add (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iio_trigger_list ; 
 int /*<<< orphan*/  iio_trigger_list_lock ; 
 int iio_trigger_register_id (struct iio_trigger*) ; 
 int iio_trigger_register_sysfs (struct iio_trigger*) ; 
 int /*<<< orphan*/  iio_trigger_unregister_id (struct iio_trigger*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int iio_trigger_register(struct iio_trigger *trig_info)
{
	int ret;

	ret = iio_trigger_register_id(trig_info);
	if (ret)
		goto error_ret;
	/* Set the name used for the sysfs directory etc */
	dev_set_name(&trig_info->dev, "trigger%ld",
		     (unsigned long) trig_info->id);

	ret = device_add(&trig_info->dev);
	if (ret)
		goto error_unregister_id;

	ret = iio_trigger_register_sysfs(trig_info);
	if (ret)
		goto error_device_del;

	/* Add to list of available triggers held by the IIO core */
	mutex_lock(&iio_trigger_list_lock);
	list_add_tail(&trig_info->list, &iio_trigger_list);
	mutex_unlock(&iio_trigger_list_lock);

	return 0;

error_device_del:
	device_del(&trig_info->dev);
error_unregister_id:
	iio_trigger_unregister_id(trig_info);
error_ret:
	return ret;
}