#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ibmpex_bmc_data {TYPE_3__* sensors; int /*<<< orphan*/  bmc_device; } ;
struct TYPE_5__ {char* name; int /*<<< orphan*/  mode; } ;
struct TYPE_8__ {TYPE_1__ attr; int /*<<< orphan*/  show; } ;
struct TYPE_7__ {TYPE_2__* attr; } ;
struct TYPE_6__ {int index; int nr; TYPE_4__ dev_attr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int POWER_SENSOR ; 
 int /*<<< orphan*/  S_IRUGO ; 
 int TEMP_SENSOR ; 
 int device_create_file (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  ibmpex_show_sensor ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int,int /*<<< orphan*/ ) ; 
 char** power_sensor_name_templates ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,int) ; 
 char** temp_sensor_name_templates ; 

__attribute__((used)) static int create_sensor(struct ibmpex_bmc_data *data, int type,
			 int counter, int sensor, int func)
{
	int err;
	char *n;

	n = kmalloc(32, GFP_KERNEL);
	if (!n)
		return -ENOMEM;

	if (type == TEMP_SENSOR)
		sprintf(n, temp_sensor_name_templates[func], "temp", counter);
	else if (type == POWER_SENSOR)
		sprintf(n, power_sensor_name_templates[func], "power", counter);

	data->sensors[sensor].attr[func].dev_attr.attr.name = n;
	data->sensors[sensor].attr[func].dev_attr.attr.mode = S_IRUGO;
	data->sensors[sensor].attr[func].dev_attr.show = ibmpex_show_sensor;
	data->sensors[sensor].attr[func].index = sensor;
	data->sensors[sensor].attr[func].nr = func;

	err = device_create_file(data->bmc_device,
				 &data->sensors[sensor].attr[func].dev_attr);
	if (err) {
		data->sensors[sensor].attr[func].dev_attr.attr.name = NULL;
		kfree(n);
		return err;
	}

	return 0;
}