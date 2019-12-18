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
struct nand_chip {int state; int options; int (* read_byte ) (struct mtd_info*) ;scalar_t__ (* dev_ready ) (struct mtd_info*) ;int /*<<< orphan*/  (* cmdfunc ) (struct mtd_info*,int /*<<< orphan*/ ,int,int) ;} ;
struct mtd_info {int dummy; } ;

/* Variables and functions */
 int FL_ERASING ; 
 int HZ ; 
 int /*<<< orphan*/  LED_FULL ; 
 int /*<<< orphan*/  LED_OFF ; 
 int /*<<< orphan*/  NAND_CMD_STATUS ; 
 int /*<<< orphan*/  NAND_CMD_STATUS_MULTI ; 
 int NAND_IS_AND ; 
 int NAND_STATUS_READY ; 
 int /*<<< orphan*/  cond_resched () ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  led_trigger_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nand_led_trigger ; 
 int /*<<< orphan*/  ndelay (int) ; 
 int /*<<< orphan*/  stub1 (struct mtd_info*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub2 (struct mtd_info*,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ stub3 (struct mtd_info*) ; 
 int stub4 (struct mtd_info*) ; 
 int stub5 (struct mtd_info*) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static int nand_wait(struct mtd_info *mtd, struct nand_chip *chip)
{

	unsigned long timeo = jiffies;
	int status, state = chip->state;

	if (state == FL_ERASING)
		timeo += (HZ * 400) / 1000;
	else
		timeo += (HZ * 20) / 1000;

	led_trigger_event(nand_led_trigger, LED_FULL);

	/* Apply this short delay always to ensure that we do wait tWB in
	 * any case on any machine. */
	ndelay(100);

	if ((state == FL_ERASING) && (chip->options & NAND_IS_AND))
		chip->cmdfunc(mtd, NAND_CMD_STATUS_MULTI, -1, -1);
	else
		chip->cmdfunc(mtd, NAND_CMD_STATUS, -1, -1);

	while (time_before(jiffies, timeo)) {
		if (chip->dev_ready) {
			if (chip->dev_ready(mtd))
				break;
		} else {
			if (chip->read_byte(mtd) & NAND_STATUS_READY)
				break;
		}
		cond_resched();
	}
	led_trigger_event(nand_led_trigger, LED_OFF);

	status = (int)chip->read_byte(mtd);
	return status;
}