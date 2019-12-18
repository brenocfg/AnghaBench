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
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DISPC_SIZE_DIG ; 
 int FLD_MASK (int,int) ; 
 int /*<<< orphan*/  MOD_REG_FLD (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  enable_lcd_clocks (int) ; 

void omap_dispc_set_digit_size(int x, int y)
{
	BUG_ON((x > (1 << 11)) || (y > (1 << 11)));
	enable_lcd_clocks(1);
	MOD_REG_FLD(DISPC_SIZE_DIG, FLD_MASK(16, 11) | FLD_MASK(0, 11),
			((y - 1) << 16) | (x - 1));
	enable_lcd_clocks(0);
}