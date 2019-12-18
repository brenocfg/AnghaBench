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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct rt2x00_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EFUSE_CTRL ; 
 int /*<<< orphan*/  EFUSE_CTRL_3290 ; 
 int /*<<< orphan*/  EFUSE_CTRL_PRESENT ; 
 int /*<<< orphan*/  RT3290 ; 
 int /*<<< orphan*/  rt2800_register_read (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int rt2x00_get_field32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rt2x00_rt (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 

int rt2800_efuse_detect(struct rt2x00_dev *rt2x00dev)
{
	u32 reg;
	u16 efuse_ctrl_reg;

	if (rt2x00_rt(rt2x00dev, RT3290))
		efuse_ctrl_reg = EFUSE_CTRL_3290;
	else
		efuse_ctrl_reg = EFUSE_CTRL;

	rt2800_register_read(rt2x00dev, efuse_ctrl_reg, &reg);
	return rt2x00_get_field32(reg, EFUSE_CTRL_PRESENT);
}