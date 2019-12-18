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
struct bt431_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT431_REG_WXLO ; 
 int /*<<< orphan*/  bt431_select_reg (struct bt431_regs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bt431_write_reg_inc (struct bt431_regs*,int) ; 

__attribute__((used)) static inline void bt431_init_cursor(struct bt431_regs *regs)
{
	/* no crosshair window */
	bt431_select_reg(regs, BT431_REG_WXLO);
	bt431_write_reg_inc(regs, 0x00); /* BT431_REG_WXLO */
	bt431_write_reg_inc(regs, 0x00); /* BT431_REG_WXHI */
	bt431_write_reg_inc(regs, 0x00); /* BT431_REG_WYLO */
	bt431_write_reg_inc(regs, 0x00); /* BT431_REG_WYHI */
	bt431_write_reg_inc(regs, 0x00); /* BT431_REG_WWLO */
	bt431_write_reg_inc(regs, 0x00); /* BT431_REG_WWHI */
	bt431_write_reg_inc(regs, 0x00); /* BT431_REG_WHLO */
	bt431_write_reg_inc(regs, 0x00); /* BT431_REG_WHHI */
}