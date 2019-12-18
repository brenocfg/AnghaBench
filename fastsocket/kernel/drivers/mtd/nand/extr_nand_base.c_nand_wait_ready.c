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
struct nand_chip {scalar_t__ (* dev_ready ) (struct mtd_info*) ;} ;
struct mtd_info {struct nand_chip* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  LED_FULL ; 
 int /*<<< orphan*/  LED_OFF ; 
 int jiffies ; 
 int /*<<< orphan*/  led_trigger_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nand_led_trigger ; 
 scalar_t__ stub1 (struct mtd_info*) ; 
 scalar_t__ time_before (int,unsigned long) ; 
 int /*<<< orphan*/  touch_softlockup_watchdog () ; 

void nand_wait_ready(struct mtd_info *mtd)
{
	struct nand_chip *chip = mtd->priv;
	unsigned long timeo = jiffies + 2;

	led_trigger_event(nand_led_trigger, LED_FULL);
	/* wait until command is processed or timeout occures */
	do {
		if (chip->dev_ready(mtd))
			break;
		touch_softlockup_watchdog();
	} while (time_before(jiffies, timeo));
	led_trigger_event(nand_led_trigger, LED_OFF);
}