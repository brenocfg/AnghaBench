#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {int zoom_on; int /*<<< orphan*/  update_mode_before_suspend; TYPE_1__* fbdev; int /*<<< orphan*/  (* power_up ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLIZZARD_DISPLAY_MODE ; 
 int /*<<< orphan*/  BLIZZARD_PLL_DIV ; 
 int /*<<< orphan*/  BLIZZARD_PLL_MODE ; 
 int /*<<< orphan*/  BLIZZARD_POWER_SAVE ; 
 TYPE_2__ blizzard ; 
 int blizzard_read_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blizzard_restart_sdram () ; 
 int /*<<< orphan*/  blizzard_restore_gen_regs () ; 
 int /*<<< orphan*/  blizzard_restore_pll_regs () ; 
 int /*<<< orphan*/  blizzard_set_update_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blizzard_sync () ; 
 int /*<<< orphan*/  blizzard_write_reg (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_full_screen () ; 

__attribute__((used)) static void blizzard_resume(void)
{
	u32 l;

	if (blizzard.power_up != NULL)
		blizzard.power_up(blizzard.fbdev->dev);

	l = blizzard_read_reg(BLIZZARD_POWER_SAVE);
	/* Standby, Sleep */
	l &= ~0x03;
	blizzard_write_reg(BLIZZARD_POWER_SAVE, l);

	blizzard_restore_pll_regs();
	l = blizzard_read_reg(BLIZZARD_PLL_MODE);
	l &= ~0x03;
	/* Enable PLL, counter function */
	l |= 0x1;
	blizzard_write_reg(BLIZZARD_PLL_MODE, l);

	while (!(blizzard_read_reg(BLIZZARD_PLL_DIV) & (1 << 7)))
		msleep(1);

	blizzard_restart_sdram();

	blizzard_restore_gen_regs();

	/* Enable display */
	blizzard_write_reg(BLIZZARD_DISPLAY_MODE, 0x01);

	/* the following will enable clocks as necessary */
	blizzard_set_update_mode(blizzard.update_mode_before_suspend);

	/* Force a background update */
	blizzard.zoom_on = 1;
	update_full_screen();
	blizzard_sync();
}