#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct ibmpex_bmc_data {int num_sensors; TYPE_5__* sensors; int /*<<< orphan*/  bmc_device; int /*<<< orphan*/  rx_msg_len; int /*<<< orphan*/  rx_msg_data; } ;
struct TYPE_9__ {TYPE_5__* name; } ;
struct TYPE_14__ {TYPE_1__ attr; } ;
struct TYPE_13__ {int multiplier; int in_use; TYPE_2__* attr; } ;
struct TYPE_12__ {TYPE_7__ dev_attr; } ;
struct TYPE_11__ {TYPE_7__ dev_attr; } ;
struct TYPE_10__ {TYPE_7__ dev_attr; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PEX_NUM_SENSOR_FUNCS ; 
 int POWER_SENSOR ; 
 int TEMP_SENSOR ; 
 int create_sensor (struct ibmpex_bmc_data*,int,int,int,int) ; 
 int device_create_file (int /*<<< orphan*/ ,TYPE_7__*) ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ ,TYPE_7__*) ; 
 int ibmpex_query_sensor_count (struct ibmpex_bmc_data*) ; 
 int ibmpex_query_sensor_name (struct ibmpex_bmc_data*,int) ; 
 scalar_t__ is_power_sensor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ is_temp_sensor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_5__*) ; 
 TYPE_5__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int power_sensor_multiplier (struct ibmpex_bmc_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__ sensor_dev_attr_name ; 
 TYPE_3__ sensor_dev_attr_reset_high_low ; 

__attribute__((used)) static int ibmpex_find_sensors(struct ibmpex_bmc_data *data)
{
	int i, j, err;
	int sensor_type;
	int sensor_counter;
	int num_power = 0;
	int num_temp = 0;

	err = ibmpex_query_sensor_count(data);
	if (err <= 0)
		return -ENOENT;
	data->num_sensors = err;

	data->sensors = kzalloc(data->num_sensors * sizeof(*data->sensors),
				GFP_KERNEL);
	if (!data->sensors)
		return -ENOMEM;

	for (i = 0; i < data->num_sensors; i++) {
		err = ibmpex_query_sensor_name(data, i);
		if (err)
			continue;

		if (is_power_sensor(data->rx_msg_data, data->rx_msg_len)) {
			sensor_type = POWER_SENSOR;
			num_power++;
			sensor_counter = num_power;
			data->sensors[i].multiplier =
				power_sensor_multiplier(data,
							data->rx_msg_data,
							data->rx_msg_len);
		} else if (is_temp_sensor(data->rx_msg_data,
					  data->rx_msg_len)) {
			sensor_type = TEMP_SENSOR;
			num_temp++;
			sensor_counter = num_temp;
			data->sensors[i].multiplier = 1000;
		} else
			continue;

		data->sensors[i].in_use = 1;

		/* Create attributes */
		for (j = 0; j < PEX_NUM_SENSOR_FUNCS; j++) {
			err = create_sensor(data, sensor_type, sensor_counter,
					    i, j);
			if (err)
				goto exit_remove;
		}
	}

	err = device_create_file(data->bmc_device,
			&sensor_dev_attr_reset_high_low.dev_attr);
	if (err)
		goto exit_remove;

	err = device_create_file(data->bmc_device,
			&sensor_dev_attr_name.dev_attr);
	if (err)
		goto exit_remove;

	return 0;

exit_remove:
	device_remove_file(data->bmc_device,
			   &sensor_dev_attr_reset_high_low.dev_attr);
	device_remove_file(data->bmc_device, &sensor_dev_attr_name.dev_attr);
	for (i = 0; i < data->num_sensors; i++)
		for (j = 0; j < PEX_NUM_SENSOR_FUNCS; j++) {
			if (!data->sensors[i].attr[j].dev_attr.attr.name)
				continue;
			device_remove_file(data->bmc_device,
				&data->sensors[i].attr[j].dev_attr);
			kfree(data->sensors[i].attr[j].dev_attr.attr.name);
		}

	kfree(data->sensors);
	return err;
}