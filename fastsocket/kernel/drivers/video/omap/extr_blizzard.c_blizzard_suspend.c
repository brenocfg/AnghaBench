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
struct TYPE_4__ {TYPE_1__* fbdev; int /*<<< orphan*/  (* power_down ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  update_mode; int /*<<< orphan*/  update_mode_before_suspend; scalar_t__ last_color_mode; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLIZZARD_PLL_MODE ; 
 int /*<<< orphan*/  BLIZZARD_POWER_SAVE ; 
 int /*<<< orphan*/  OMAPFB_UPDATE_DISABLED ; 
 TYPE_2__ blizzard ; 
 int blizzard_read_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blizzard_save_all_regs () ; 
 int /*<<< orphan*/  blizzard_set_update_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blizzard_stop_sdram () ; 
 int /*<<< orphan*/  blizzard_sync () ; 
 int /*<<< orphan*/  blizzard_write_reg (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  update_full_screen () ; 

__attribute__((used)) static void blizzard_suspend(void)
{
	u32 l;
	unsigned long tmo;

	if (blizzard.last_color_mode) {
		update_full_screen();
		blizzard_sync();
	}
	blizzard.update_mode_before_suspend = blizzard.update_mode;
	/* the following will disable clocks as well */
	blizzard_set_update_mode(OMAPFB_UPDATE_DISABLED);

	blizzard_save_all_regs();

	blizzard_stop_sdram();

	l = blizzard_read_reg(BLIZZARD_POWER_SAVE);
	/* Standby, Sleep. We assume we use an external clock. */
	l |= 0x03;
	blizzard_write_reg(BLIZZARD_POWER_SAVE, l);

	tmo = jiffies + msecs_to_jiffies(100);
	while (!(blizzard_read_reg(BLIZZARD_PLL_MODE) & (1 << 1))) {
		if (time_after(jiffies, tmo)) {
			dev_err(blizzard.fbdev->dev,
				"s1d1374x: sleep timeout, stopping PLL manually\n");
			l = blizzard_read_reg(BLIZZARD_PLL_MODE);
			l &= ~0x03;
			/* Disable PLL, counter function */
			l |= 0x2;
			blizzard_write_reg(BLIZZARD_PLL_MODE, l);
			break;
		}
		msleep(1);
	}

	if (blizzard.power_down != NULL)
		blizzard.power_down(blizzard.fbdev->dev);
}