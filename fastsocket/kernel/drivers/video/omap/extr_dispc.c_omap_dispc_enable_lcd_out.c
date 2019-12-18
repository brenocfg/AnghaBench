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

/* Variables and functions */
 int /*<<< orphan*/  DISPC_CONTROL ; 
 int /*<<< orphan*/  MOD_REG_FLD (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  enable_lcd_clocks (int) ; 

void omap_dispc_enable_lcd_out(int enable)
{
	enable_lcd_clocks(1);
	MOD_REG_FLD(DISPC_CONTROL, 1, enable ? 1 : 0);
	enable_lcd_clocks(0);
}