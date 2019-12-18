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
struct TYPE_6__ {int count; TYPE_2__* elements; } ;
union acpi_object {TYPE_3__ package; } ;
struct atk_data {int disable_ec; int old_interface; int /*<<< orphan*/  atk_handle; int /*<<< orphan*/  sensor_list; struct acpi_device* acpi_dev; } ;
struct acpi_device {struct atk_data* driver_data; int /*<<< orphan*/  dev; int /*<<< orphan*/  handle; } ;
struct acpi_buffer {union acpi_object* pointer; int /*<<< orphan*/  length; } ;
typedef  scalar_t__ acpi_status ;
struct TYPE_4__ {int /*<<< orphan*/  pointer; } ;
struct TYPE_5__ {scalar_t__ type; TYPE_1__ string; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ALLOCATE_BUFFER ; 
 int /*<<< orphan*/  ACPI_FREE (union acpi_object*) ; 
 int /*<<< orphan*/  ACPI_TYPE_PACKAGE ; 
 scalar_t__ ACPI_TYPE_STRING ; 
 scalar_t__ AE_OK ; 
 int /*<<< orphan*/  BOARD_ID ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ acpi_evaluate_object_typed (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct acpi_buffer*,int /*<<< orphan*/ ) ; 
 int atk_check_new_if (struct atk_data*) ; 
 int atk_check_old_if (struct atk_data*) ; 
 int /*<<< orphan*/  atk_ec_ctl (struct atk_data*,int /*<<< orphan*/ ) ; 
 int atk_enumerate_new_hwmon (struct atk_data*) ; 
 int atk_enumerate_old_hwmon (struct atk_data*) ; 
 int /*<<< orphan*/  atk_free_sensors (struct atk_data*) ; 
 int atk_register_hwmon (struct atk_data*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  kfree (struct atk_data*) ; 
 struct atk_data* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int atk_add(struct acpi_device *device)
{
	acpi_status ret;
	int err;
	struct acpi_buffer buf;
	union acpi_object *obj;
	struct atk_data *data;

	dev_dbg(&device->dev, "adding...\n");

	data = kzalloc(sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	data->acpi_dev = device;
	data->atk_handle = device->handle;
	INIT_LIST_HEAD(&data->sensor_list);
	data->disable_ec = false;

	buf.length = ACPI_ALLOCATE_BUFFER;
	ret = acpi_evaluate_object_typed(data->atk_handle, BOARD_ID, NULL,
			&buf, ACPI_TYPE_PACKAGE);
	if (ret != AE_OK) {
		dev_dbg(&device->dev, "atk: method MBIF not found\n");
		err = -ENODEV;
		goto out;
	}

	obj = buf.pointer;
	if (obj->package.count >= 2 &&
			obj->package.elements[1].type == ACPI_TYPE_STRING) {
		dev_dbg(&device->dev, "board ID = %s\n",
				obj->package.elements[1].string.pointer);
	}
	ACPI_FREE(buf.pointer);

	/* Check for hwmon methods: first check "old" style methods; note that
	 * both may be present: in this case we stick to the old interface;
	 * analysis of multiple DSDTs indicates that when both interfaces
	 * are present the new one (GGRP/GITM) is not functional.
	 */
	err = atk_check_old_if(data);
	if (!err) {
		dev_dbg(&device->dev, "Using old hwmon interface\n");
		data->old_interface = true;
	} else {
		err = atk_check_new_if(data);
		if (err)
			goto out;

		dev_dbg(&device->dev, "Using new hwmon interface\n");
		data->old_interface = false;
	}

	if (data->old_interface)
		err = atk_enumerate_old_hwmon(data);
	else
		err = atk_enumerate_new_hwmon(data);
	if (err < 0)
		goto out;
	if (err == 0) {
		dev_info(&device->dev,
			 "No usable sensor detected, bailing out\n");
		err = -ENODEV;
		goto out;
	}

	err = atk_register_hwmon(data);
	if (err)
		goto cleanup;

	device->driver_data = data;
	return 0;
cleanup:
	atk_free_sensors(data);
out:
	if (data->disable_ec)
		atk_ec_ctl(data, 0);
	kfree(data);
	return err;
}