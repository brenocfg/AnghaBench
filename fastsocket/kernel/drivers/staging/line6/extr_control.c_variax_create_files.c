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
 int /*<<< orphan*/  CHECK_RETURN (int /*<<< orphan*/ ) ; 
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
 int /*<<< orphan*/  device_create_file (struct device*,int /*<<< orphan*/ *) ; 

int variax_create_files(int firmware, int type, struct device *dev)
{
	int err;
	CHECK_RETURN(device_create_file(dev, &dev_attr_body));
	CHECK_RETURN(device_create_file(dev, &dev_attr_pickup1_enable));
	CHECK_RETURN(device_create_file(dev, &dev_attr_pickup1_type));
	CHECK_RETURN(device_create_file(dev, &dev_attr_pickup1_position));
	CHECK_RETURN(device_create_file(dev, &dev_attr_pickup1_angle));
	CHECK_RETURN(device_create_file(dev, &dev_attr_pickup1_level));
	CHECK_RETURN(device_create_file(dev, &dev_attr_pickup2_enable));
	CHECK_RETURN(device_create_file(dev, &dev_attr_pickup2_type));
	CHECK_RETURN(device_create_file(dev, &dev_attr_pickup2_position));
	CHECK_RETURN(device_create_file(dev, &dev_attr_pickup2_angle));
	CHECK_RETURN(device_create_file(dev, &dev_attr_pickup2_level));
	CHECK_RETURN(device_create_file(dev, &dev_attr_pickup_phase));
	CHECK_RETURN(device_create_file(dev, &dev_attr_capacitance));
	CHECK_RETURN(device_create_file(dev, &dev_attr_tone_resistance));
	CHECK_RETURN(device_create_file(dev, &dev_attr_volume_resistance));
	CHECK_RETURN(device_create_file(dev, &dev_attr_taper));
	CHECK_RETURN(device_create_file(dev, &dev_attr_tone_dump));
	CHECK_RETURN(device_create_file(dev, &dev_attr_save_tone));
	CHECK_RETURN(device_create_file(dev, &dev_attr_volume_dump));
	CHECK_RETURN(device_create_file(dev, &dev_attr_tuning_enable));
	CHECK_RETURN(device_create_file(dev, &dev_attr_tuning6));
	CHECK_RETURN(device_create_file(dev, &dev_attr_tuning5));
	CHECK_RETURN(device_create_file(dev, &dev_attr_tuning4));
	CHECK_RETURN(device_create_file(dev, &dev_attr_tuning3));
	CHECK_RETURN(device_create_file(dev, &dev_attr_tuning2));
	CHECK_RETURN(device_create_file(dev, &dev_attr_tuning1));
	CHECK_RETURN(device_create_file(dev, &dev_attr_detune6));
	CHECK_RETURN(device_create_file(dev, &dev_attr_detune5));
	CHECK_RETURN(device_create_file(dev, &dev_attr_detune4));
	CHECK_RETURN(device_create_file(dev, &dev_attr_detune3));
	CHECK_RETURN(device_create_file(dev, &dev_attr_detune2));
	CHECK_RETURN(device_create_file(dev, &dev_attr_detune1));
	CHECK_RETURN(device_create_file(dev, &dev_attr_mix6));
	CHECK_RETURN(device_create_file(dev, &dev_attr_mix5));
	CHECK_RETURN(device_create_file(dev, &dev_attr_mix4));
	CHECK_RETURN(device_create_file(dev, &dev_attr_mix3));
	CHECK_RETURN(device_create_file(dev, &dev_attr_mix2));
	CHECK_RETURN(device_create_file(dev, &dev_attr_mix1));
	CHECK_RETURN(device_create_file(dev, &dev_attr_pickup_wiring));
  return 0;
}