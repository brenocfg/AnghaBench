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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int /*<<< orphan*/  TWL4030_MODULE_RTC ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int) ; 
 int twl4030_i2c_write_u8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int twl4030_rtc_write_u8(u8 data, u8 reg)
{
	int ret;

	ret = twl4030_i2c_write_u8(TWL4030_MODULE_RTC, data, reg);
	if (ret < 0)
		pr_err("twl4030_rtc: Could not write TWL4030"
		       "register %X - error %d\n", reg, ret);
	return ret;
}