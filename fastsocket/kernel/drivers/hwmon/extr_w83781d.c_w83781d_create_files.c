#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_57__   TYPE_9__ ;
typedef  struct TYPE_56__   TYPE_8__ ;
typedef  struct TYPE_55__   TYPE_7__ ;
typedef  struct TYPE_54__   TYPE_6__ ;
typedef  struct TYPE_53__   TYPE_5__ ;
typedef  struct TYPE_52__   TYPE_4__ ;
typedef  struct TYPE_51__   TYPE_3__ ;
typedef  struct TYPE_50__   TYPE_2__ ;
typedef  struct TYPE_49__   TYPE_28__ ;
typedef  struct TYPE_48__   TYPE_27__ ;
typedef  struct TYPE_47__   TYPE_26__ ;
typedef  struct TYPE_46__   TYPE_25__ ;
typedef  struct TYPE_45__   TYPE_24__ ;
typedef  struct TYPE_44__   TYPE_23__ ;
typedef  struct TYPE_43__   TYPE_22__ ;
typedef  struct TYPE_42__   TYPE_21__ ;
typedef  struct TYPE_41__   TYPE_20__ ;
typedef  struct TYPE_40__   TYPE_1__ ;
typedef  struct TYPE_39__   TYPE_19__ ;
typedef  struct TYPE_38__   TYPE_18__ ;
typedef  struct TYPE_37__   TYPE_17__ ;
typedef  struct TYPE_36__   TYPE_16__ ;
typedef  struct TYPE_35__   TYPE_15__ ;
typedef  struct TYPE_34__   TYPE_14__ ;
typedef  struct TYPE_33__   TYPE_13__ ;
typedef  struct TYPE_32__   TYPE_12__ ;
typedef  struct TYPE_31__   TYPE_11__ ;
typedef  struct TYPE_30__   TYPE_10__ ;

/* Type definitions */
struct device {int /*<<< orphan*/  kobj; } ;
struct TYPE_49__ {int /*<<< orphan*/  attr; } ;
struct TYPE_57__ {TYPE_28__ dev_attr; } ;
struct TYPE_56__ {TYPE_28__ dev_attr; } ;
struct TYPE_55__ {TYPE_28__ dev_attr; } ;
struct TYPE_54__ {TYPE_28__ dev_attr; } ;
struct TYPE_53__ {TYPE_28__ dev_attr; } ;
struct TYPE_52__ {TYPE_28__ dev_attr; } ;
struct TYPE_51__ {TYPE_28__ dev_attr; } ;
struct TYPE_50__ {TYPE_28__ dev_attr; } ;
struct TYPE_48__ {TYPE_28__ dev_attr; } ;
struct TYPE_47__ {TYPE_28__ dev_attr; } ;
struct TYPE_46__ {TYPE_28__ dev_attr; } ;
struct TYPE_45__ {TYPE_28__ dev_attr; } ;
struct TYPE_44__ {TYPE_28__ dev_attr; } ;
struct TYPE_43__ {TYPE_28__ dev_attr; } ;
struct TYPE_42__ {TYPE_28__ dev_attr; } ;
struct TYPE_41__ {TYPE_28__ dev_attr; } ;
struct TYPE_40__ {TYPE_28__ dev_attr; } ;
struct TYPE_39__ {TYPE_28__ dev_attr; } ;
struct TYPE_38__ {TYPE_28__ dev_attr; } ;
struct TYPE_37__ {TYPE_28__ dev_attr; } ;
struct TYPE_36__ {TYPE_28__ dev_attr; } ;
struct TYPE_35__ {TYPE_28__ dev_attr; } ;
struct TYPE_34__ {TYPE_28__ dev_attr; } ;
struct TYPE_33__ {TYPE_28__ dev_attr; } ;
struct TYPE_32__ {TYPE_28__ dev_attr; } ;
struct TYPE_31__ {TYPE_28__ dev_attr; } ;
struct TYPE_30__ {TYPE_28__ dev_attr; } ;

/* Variables and functions */
 int S_IRUGO ; 
 int S_IWUSR ; 
 int as99127f ; 
 TYPE_28__ dev_attr_pwm2_enable ; 
 int device_create_file (struct device*,TYPE_28__*) ; 
 TYPE_27__ sensor_dev_attr_in1_alarm ; 
 TYPE_26__ sensor_dev_attr_in1_beep ; 
 TYPE_25__ sensor_dev_attr_in1_input ; 
 TYPE_24__ sensor_dev_attr_in1_max ; 
 TYPE_23__ sensor_dev_attr_in1_min ; 
 TYPE_22__ sensor_dev_attr_in7_alarm ; 
 TYPE_21__ sensor_dev_attr_in7_beep ; 
 TYPE_20__ sensor_dev_attr_in7_input ; 
 TYPE_19__ sensor_dev_attr_in7_max ; 
 TYPE_18__ sensor_dev_attr_in7_min ; 
 TYPE_17__ sensor_dev_attr_in8_alarm ; 
 TYPE_16__ sensor_dev_attr_in8_beep ; 
 TYPE_15__ sensor_dev_attr_in8_input ; 
 TYPE_14__ sensor_dev_attr_in8_max ; 
 TYPE_13__ sensor_dev_attr_in8_min ; 
 TYPE_12__ sensor_dev_attr_pwm1 ; 
 TYPE_11__ sensor_dev_attr_pwm2 ; 
 TYPE_10__ sensor_dev_attr_pwm3 ; 
 TYPE_9__ sensor_dev_attr_pwm4 ; 
 TYPE_8__ sensor_dev_attr_temp1_type ; 
 TYPE_7__ sensor_dev_attr_temp2_type ; 
 TYPE_6__ sensor_dev_attr_temp3_alarm ; 
 TYPE_5__ sensor_dev_attr_temp3_beep ; 
 TYPE_4__ sensor_dev_attr_temp3_input ; 
 TYPE_3__ sensor_dev_attr_temp3_max ; 
 TYPE_2__ sensor_dev_attr_temp3_max_hyst ; 
 TYPE_1__ sensor_dev_attr_temp3_type ; 
 int sysfs_chmod_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int w83781d ; 
 int /*<<< orphan*/  w83781d_group ; 
 int w83782d ; 
 int w83783s ; 

__attribute__((used)) static int
w83781d_create_files(struct device *dev, int kind, int is_isa)
{
	int err;

	if ((err = sysfs_create_group(&dev->kobj, &w83781d_group)))
		return err;

	if (kind != w83783s) {
		if ((err = device_create_file(dev,
				&sensor_dev_attr_in1_input.dev_attr))
		    || (err = device_create_file(dev,
				&sensor_dev_attr_in1_min.dev_attr))
		    || (err = device_create_file(dev,
				&sensor_dev_attr_in1_max.dev_attr))
		    || (err = device_create_file(dev,
				&sensor_dev_attr_in1_alarm.dev_attr))
		    || (err = device_create_file(dev,
				&sensor_dev_attr_in1_beep.dev_attr)))
			return err;
	}
	if (kind != as99127f && kind != w83781d && kind != w83783s) {
		if ((err = device_create_file(dev,
				&sensor_dev_attr_in7_input.dev_attr))
		    || (err = device_create_file(dev,
				&sensor_dev_attr_in7_min.dev_attr))
		    || (err = device_create_file(dev,
				&sensor_dev_attr_in7_max.dev_attr))
		    || (err = device_create_file(dev,
				&sensor_dev_attr_in7_alarm.dev_attr))
		    || (err = device_create_file(dev,
				&sensor_dev_attr_in7_beep.dev_attr))
		    || (err = device_create_file(dev,
				&sensor_dev_attr_in8_input.dev_attr))
		    || (err = device_create_file(dev,
				&sensor_dev_attr_in8_min.dev_attr))
		    || (err = device_create_file(dev,
				&sensor_dev_attr_in8_max.dev_attr))
		    || (err = device_create_file(dev,
				&sensor_dev_attr_in8_alarm.dev_attr))
		    || (err = device_create_file(dev,
				&sensor_dev_attr_in8_beep.dev_attr)))
			return err;
	}
	if (kind != w83783s) {
		if ((err = device_create_file(dev,
				&sensor_dev_attr_temp3_input.dev_attr))
		    || (err = device_create_file(dev,
				&sensor_dev_attr_temp3_max.dev_attr))
		    || (err = device_create_file(dev,
				&sensor_dev_attr_temp3_max_hyst.dev_attr))
		    || (err = device_create_file(dev,
				&sensor_dev_attr_temp3_alarm.dev_attr))
		    || (err = device_create_file(dev,
				&sensor_dev_attr_temp3_beep.dev_attr)))
			return err;

		if (kind != w83781d) {
			err = sysfs_chmod_file(&dev->kobj,
				&sensor_dev_attr_temp3_alarm.dev_attr.attr,
				S_IRUGO | S_IWUSR);
			if (err)
				return err;
		}
	}

	if (kind != w83781d && kind != as99127f) {
		if ((err = device_create_file(dev,
				&sensor_dev_attr_pwm1.dev_attr))
		    || (err = device_create_file(dev,
				&sensor_dev_attr_pwm2.dev_attr))
		    || (err = device_create_file(dev, &dev_attr_pwm2_enable)))
			return err;
	}
	if (kind == w83782d && !is_isa) {
		if ((err = device_create_file(dev,
				&sensor_dev_attr_pwm3.dev_attr))
		    || (err = device_create_file(dev,
				&sensor_dev_attr_pwm4.dev_attr)))
			return err;
	}

	if (kind != as99127f && kind != w83781d) {
		if ((err = device_create_file(dev,
				&sensor_dev_attr_temp1_type.dev_attr))
		    || (err = device_create_file(dev,
				&sensor_dev_attr_temp2_type.dev_attr)))
			return err;
		if (kind != w83783s) {
			if ((err = device_create_file(dev,
					&sensor_dev_attr_temp3_type.dev_attr)))
				return err;
		}
	}

	return 0;
}