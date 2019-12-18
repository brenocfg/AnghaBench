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
typedef  int /*<<< orphan*/  u32 ;
struct twl4030_keypad {int /*<<< orphan*/  dbg_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  TWL4030_MODULE_KEYPAD ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int) ; 
 int twl4030_i2c_read (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int twl4030_kpread(struct twl4030_keypad *kp,
		u8 *data, u32 reg, u8 num_bytes)
{
	int ret = twl4030_i2c_read(TWL4030_MODULE_KEYPAD, data, reg, num_bytes);

	if (ret < 0)
		dev_warn(kp->dbg_dev,
			"Couldn't read TWL4030: %X - ret %d[%x]\n",
			 reg, ret, ret);

	return ret;
}