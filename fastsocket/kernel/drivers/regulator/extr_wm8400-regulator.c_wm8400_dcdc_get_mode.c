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
typedef  int u16 ;
struct wm8400 {int dummy; } ;
struct regulator_dev {int dummy; } ;

/* Variables and functions */
 unsigned int REGULATOR_MODE_FAST ; 
 unsigned int REGULATOR_MODE_IDLE ; 
 unsigned int REGULATOR_MODE_NORMAL ; 
 unsigned int REGULATOR_MODE_STANDBY ; 
 int WM8400_DC1_ACTIVE ; 
 int WM8400_DC1_FRC_PWM ; 
 int WM8400_DC1_SLEEP ; 
 int WM8400_DCDC1 ; 
 scalar_t__ WM8400_DCDC1_CONTROL_1 ; 
 struct wm8400* rdev_get_drvdata (struct regulator_dev*) ; 
 int rdev_get_id (struct regulator_dev*) ; 
 int wm8400_block_read (struct wm8400*,scalar_t__,int,int*) ; 

__attribute__((used)) static unsigned int wm8400_dcdc_get_mode(struct regulator_dev *dev)
{
	struct wm8400 *wm8400 = rdev_get_drvdata(dev);
	int offset = (rdev_get_id(dev) - WM8400_DCDC1) * 2;
	u16 data[2];
	int ret;

	ret = wm8400_block_read(wm8400, WM8400_DCDC1_CONTROL_1 + offset, 2,
				data);
	if (ret != 0)
		return 0;

	/* Datasheet: hibernate */
	if (data[0] & WM8400_DC1_SLEEP)
		return REGULATOR_MODE_STANDBY;

	/* Datasheet: standby */
	if (!(data[0] & WM8400_DC1_ACTIVE))
		return REGULATOR_MODE_IDLE;

	/* Datasheet: active with or without force PWM */
	if (data[1] & WM8400_DC1_FRC_PWM)
		return REGULATOR_MODE_FAST;
	else
		return REGULATOR_MODE_NORMAL;
}