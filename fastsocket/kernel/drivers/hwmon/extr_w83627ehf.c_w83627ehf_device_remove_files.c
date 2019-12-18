#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_40__   TYPE_8__ ;
typedef  struct TYPE_39__   TYPE_7__ ;
typedef  struct TYPE_38__   TYPE_6__ ;
typedef  struct TYPE_37__   TYPE_5__ ;
typedef  struct TYPE_36__   TYPE_4__ ;
typedef  struct TYPE_35__   TYPE_3__ ;
typedef  struct TYPE_34__   TYPE_2__ ;
typedef  struct TYPE_33__   TYPE_20__ ;
typedef  struct TYPE_32__   TYPE_1__ ;
typedef  struct TYPE_31__   TYPE_19__ ;
typedef  struct TYPE_30__   TYPE_18__ ;
typedef  struct TYPE_29__   TYPE_17__ ;
typedef  struct TYPE_28__   TYPE_16__ ;
typedef  struct TYPE_27__   TYPE_15__ ;
typedef  struct TYPE_26__   TYPE_14__ ;
typedef  struct TYPE_25__   TYPE_13__ ;
typedef  struct TYPE_24__   TYPE_12__ ;
typedef  struct TYPE_23__   TYPE_11__ ;
typedef  struct TYPE_22__   TYPE_10__ ;

/* Type definitions */
struct w83627ehf_data {int in_num; int pwm_num; scalar_t__ temp3_disable; scalar_t__ in6_skip; } ;
struct device {int dummy; } ;
struct TYPE_40__ {int /*<<< orphan*/  dev_attr; } ;
struct TYPE_39__ {int /*<<< orphan*/  dev_attr; } ;
struct TYPE_38__ {int /*<<< orphan*/  dev_attr; } ;
struct TYPE_37__ {int /*<<< orphan*/  dev_attr; } ;
struct TYPE_36__ {int /*<<< orphan*/  dev_attr; } ;
struct TYPE_35__ {int /*<<< orphan*/  dev_attr; } ;
struct TYPE_34__ {int /*<<< orphan*/  dev_attr; } ;
struct TYPE_33__ {int /*<<< orphan*/  dev_attr; } ;
struct TYPE_32__ {int /*<<< orphan*/  dev_attr; } ;
struct TYPE_31__ {int /*<<< orphan*/  dev_attr; } ;
struct TYPE_30__ {int /*<<< orphan*/  dev_attr; } ;
struct TYPE_29__ {int /*<<< orphan*/  dev_attr; } ;
struct TYPE_28__ {int /*<<< orphan*/  dev_attr; } ;
struct TYPE_27__ {int /*<<< orphan*/  dev_attr; } ;
struct TYPE_26__ {int /*<<< orphan*/  dev_attr; } ;
struct TYPE_25__ {int /*<<< orphan*/  dev_attr; } ;
struct TYPE_24__ {int /*<<< orphan*/  dev_attr; } ;
struct TYPE_23__ {int /*<<< orphan*/  dev_attr; } ;
struct TYPE_22__ {int /*<<< orphan*/  dev_attr; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_8__*) ; 
 int /*<<< orphan*/  dev_attr_cpu0_vid ; 
 int /*<<< orphan*/  dev_attr_name ; 
 struct w83627ehf_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  device_remove_file (struct device*,int /*<<< orphan*/ *) ; 
 TYPE_20__* sda_fan_alarm ; 
 TYPE_19__* sda_fan_div ; 
 TYPE_18__* sda_fan_input ; 
 TYPE_17__* sda_fan_min ; 
 TYPE_16__* sda_in_alarm ; 
 TYPE_15__* sda_in_input ; 
 TYPE_14__* sda_in_max ; 
 TYPE_13__* sda_in_min ; 
 TYPE_12__* sda_pwm ; 
 TYPE_11__* sda_pwm_enable ; 
 TYPE_10__* sda_pwm_mode ; 
 TYPE_8__* sda_sf3_arrays ; 
 TYPE_8__* sda_sf3_arrays_fan4 ; 
 TYPE_7__* sda_target_temp ; 
 TYPE_6__* sda_temp_alarm ; 
 TYPE_5__* sda_temp_input ; 
 TYPE_4__* sda_temp_max ; 
 TYPE_3__* sda_temp_max_hyst ; 
 TYPE_2__* sda_temp_type ; 
 TYPE_1__* sda_tolerance ; 

__attribute__((used)) static void w83627ehf_device_remove_files(struct device *dev)
{
	/* some entries in the following arrays may not have been used in
	 * device_create_file(), but device_remove_file() will ignore them */
	int i;
	struct w83627ehf_data *data = dev_get_drvdata(dev);

	for (i = 0; i < ARRAY_SIZE(sda_sf3_arrays); i++)
		device_remove_file(dev, &sda_sf3_arrays[i].dev_attr);
	for (i = 0; i < ARRAY_SIZE(sda_sf3_arrays_fan4); i++)
		device_remove_file(dev, &sda_sf3_arrays_fan4[i].dev_attr);
	for (i = 0; i < data->in_num; i++) {
		if ((i == 6) && data->in6_skip)
			continue;
		device_remove_file(dev, &sda_in_input[i].dev_attr);
		device_remove_file(dev, &sda_in_alarm[i].dev_attr);
		device_remove_file(dev, &sda_in_min[i].dev_attr);
		device_remove_file(dev, &sda_in_max[i].dev_attr);
	}
	for (i = 0; i < 5; i++) {
		device_remove_file(dev, &sda_fan_input[i].dev_attr);
		device_remove_file(dev, &sda_fan_alarm[i].dev_attr);
		device_remove_file(dev, &sda_fan_div[i].dev_attr);
		device_remove_file(dev, &sda_fan_min[i].dev_attr);
	}
	for (i = 0; i < data->pwm_num; i++) {
		device_remove_file(dev, &sda_pwm[i].dev_attr);
		device_remove_file(dev, &sda_pwm_mode[i].dev_attr);
		device_remove_file(dev, &sda_pwm_enable[i].dev_attr);
		device_remove_file(dev, &sda_target_temp[i].dev_attr);
		device_remove_file(dev, &sda_tolerance[i].dev_attr);
	}
	for (i = 0; i < 3; i++) {
		if ((i == 2) && data->temp3_disable)
			continue;
		device_remove_file(dev, &sda_temp_input[i].dev_attr);
		device_remove_file(dev, &sda_temp_max[i].dev_attr);
		device_remove_file(dev, &sda_temp_max_hyst[i].dev_attr);
		device_remove_file(dev, &sda_temp_alarm[i].dev_attr);
		device_remove_file(dev, &sda_temp_type[i].dev_attr);
	}

	device_remove_file(dev, &dev_attr_name);
	device_remove_file(dev, &dev_attr_cpu0_vid);
}