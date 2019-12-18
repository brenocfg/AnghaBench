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
struct TYPE_4__ {TYPE_1__* fbdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLIZZARD_MEM_BANK0_ACTIVATE ; 
 int /*<<< orphan*/  BLIZZARD_MEM_BANK0_STATUS ; 
 TYPE_2__ blizzard ; 
 int blizzard_read_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blizzard_write_reg (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void blizzard_restart_sdram(void)
{
	unsigned long tmo;

	blizzard_write_reg(BLIZZARD_MEM_BANK0_ACTIVATE, 0);
	udelay(50);
	blizzard_write_reg(BLIZZARD_MEM_BANK0_ACTIVATE, 1);
	tmo = jiffies + msecs_to_jiffies(200);
	while (!(blizzard_read_reg(BLIZZARD_MEM_BANK0_STATUS) & 0x01)) {
		if (time_after(jiffies, tmo)) {
			dev_err(blizzard.fbdev->dev,
					"s1d1374x: SDRAM not ready\n");
			break;
		}
		msleep(1);
	}
}