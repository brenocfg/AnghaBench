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
 int /*<<< orphan*/  BLIZZARD_NDISP_CTRL_STATUS ; 
 TYPE_2__ blizzard ; 
 int blizzard_read_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 scalar_t__ printk_ratelimit () ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 

__attribute__((used)) static void blizzard_wait_yyc(void)
{
	unsigned long tmo = jiffies + msecs_to_jiffies(30);

	while (blizzard_read_reg(BLIZZARD_NDISP_CTRL_STATUS) & (1 << 4)) {
		if (time_after(jiffies, tmo)) {
			if (printk_ratelimit())
				dev_err(blizzard.fbdev->dev,
					"s1d1374x: YYC not ready\n");
			break;
		}
	}
}