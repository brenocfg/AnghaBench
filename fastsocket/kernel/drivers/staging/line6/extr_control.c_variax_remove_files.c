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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_attr_body ; 
 int /*<<< orphan*/  dev_attr_capacitance ; 
 int /*<<< orphan*/  dev_attr_detune1 ; 
 int /*<<< orphan*/  dev_attr_detune2 ; 
 int /*<<< orphan*/  dev_attr_detune3 ; 
 int /*<<< orphan*/  dev_attr_detune4 ; 
 int /*<<< orphan*/  dev_attr_detune5 ; 
 int /*<<< orphan*/  dev_attr_detune6 ; 
 int /*<<< orphan*/  dev_attr_mix1 ; 
 int /*<<< orphan*/  dev_attr_mix2 ; 
 int /*<<< orphan*/  dev_attr_mix3 ; 
 int /*<<< orphan*/  dev_attr_mix4 ; 
 int /*<<< orphan*/  dev_attr_mix5 ; 
 int /*<<< orphan*/  dev_attr_mix6 ; 
 int /*<<< orphan*/  dev_attr_pickup1_angle ; 
 int /*<<< orphan*/  dev_attr_pickup1_enable ; 
 int /*<<< orphan*/  dev_attr_pickup1_level ; 
 int /*<<< orphan*/  dev_attr_pickup1_position ; 
 int /*<<< orphan*/  dev_attr_pickup1_type ; 
 int /*<<< orphan*/  dev_attr_pickup2_angle ; 
 int /*<<< orphan*/  dev_attr_pickup2_enable ; 
 int /*<<< orphan*/  dev_attr_pickup2_level ; 
 int /*<<< orphan*/  dev_attr_pickup2_position ; 
 int /*<<< orphan*/  dev_attr_pickup2_type ; 
 int /*<<< orphan*/  dev_attr_pickup_phase ; 
 int /*<<< orphan*/  dev_attr_pickup_wiring ; 
 int /*<<< orphan*/  dev_attr_save_tone ; 
 int /*<<< orphan*/  dev_attr_taper ; 
 int /*<<< orphan*/  dev_attr_tone_dump ; 
 int /*<<< orphan*/  dev_attr_tone_resistance ; 
 int /*<<< orphan*/  dev_attr_tuning1 ; 
 int /*<<< orphan*/  dev_attr_tuning2 ; 
 int /*<<< orphan*/  dev_attr_tuning3 ; 
 int /*<<< orphan*/  dev_attr_tuning4 ; 
 int /*<<< orphan*/  dev_attr_tuning5 ; 
 int /*<<< orphan*/  dev_attr_tuning6 ; 
 int /*<<< orphan*/  dev_attr_tuning_enable ; 
 int /*<<< orphan*/  dev_attr_volume_dump ; 
 int /*<<< orphan*/  dev_attr_volume_resistance ; 
 int /*<<< orphan*/  device_remove_file (struct device*,int /*<<< orphan*/ *) ; 

void variax_remove_files(int firmware, int type, struct device *dev)
{
	device_remove_file(dev, &dev_attr_body);
	device_remove_file(dev, &dev_attr_pickup1_enable);
	device_remove_file(dev, &dev_attr_pickup1_type);
	device_remove_file(dev, &dev_attr_pickup1_position);
	device_remove_file(dev, &dev_attr_pickup1_angle);
	device_remove_file(dev, &dev_attr_pickup1_level);
	device_remove_file(dev, &dev_attr_pickup2_enable);
	device_remove_file(dev, &dev_attr_pickup2_type);
	device_remove_file(dev, &dev_attr_pickup2_position);
	device_remove_file(dev, &dev_attr_pickup2_angle);
	device_remove_file(dev, &dev_attr_pickup2_level);
	device_remove_file(dev, &dev_attr_pickup_phase);
	device_remove_file(dev, &dev_attr_capacitance);
	device_remove_file(dev, &dev_attr_tone_resistance);
	device_remove_file(dev, &dev_attr_volume_resistance);
	device_remove_file(dev, &dev_attr_taper);
	device_remove_file(dev, &dev_attr_tone_dump);
	device_remove_file(dev, &dev_attr_save_tone);
	device_remove_file(dev, &dev_attr_volume_dump);
	device_remove_file(dev, &dev_attr_tuning_enable);
	device_remove_file(dev, &dev_attr_tuning6);
	device_remove_file(dev, &dev_attr_tuning5);
	device_remove_file(dev, &dev_attr_tuning4);
	device_remove_file(dev, &dev_attr_tuning3);
	device_remove_file(dev, &dev_attr_tuning2);
	device_remove_file(dev, &dev_attr_tuning1);
	device_remove_file(dev, &dev_attr_detune6);
	device_remove_file(dev, &dev_attr_detune5);
	device_remove_file(dev, &dev_attr_detune4);
	device_remove_file(dev, &dev_attr_detune3);
	device_remove_file(dev, &dev_attr_detune2);
	device_remove_file(dev, &dev_attr_detune1);
	device_remove_file(dev, &dev_attr_mix6);
	device_remove_file(dev, &dev_attr_mix5);
	device_remove_file(dev, &dev_attr_mix4);
	device_remove_file(dev, &dev_attr_mix3);
	device_remove_file(dev, &dev_attr_mix2);
	device_remove_file(dev, &dev_attr_mix1);
	device_remove_file(dev, &dev_attr_pickup_wiring);
}