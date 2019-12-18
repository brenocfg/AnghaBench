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
typedef  int u32 ;
struct controller {scalar_t__ hpc_reg; } ;

/* Variables and functions */
 int HZ ; 
 scalar_t__ LED_CONTROL ; 
 scalar_t__ SLOT_MASK ; 
 int /*<<< orphan*/  long_delay (int) ; 
 int readb (scalar_t__) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  set_SOGO (struct controller*) ; 
 int /*<<< orphan*/  switch_leds (struct controller*,int,int*,int) ; 
 int /*<<< orphan*/  wait_for_ctrl_irq (struct controller*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

int cpqhp_hardware_test(struct controller *ctrl, int test_num)
{
	u32 save_LED;
	u32 work_LED;
	int loop;
	int num_of_slots;

	num_of_slots = readb(ctrl->hpc_reg + SLOT_MASK) & 0x0f;

	switch (test_num) {
	case 1:
		/* Do stuff here! */

		/* Do that funky LED thing */
		/* so we can restore them later */
		save_LED = readl(ctrl->hpc_reg + LED_CONTROL);
		work_LED = 0x01010101;
		switch_leds(ctrl, num_of_slots, &work_LED, 0);
		switch_leds(ctrl, num_of_slots, &work_LED, 1);
		switch_leds(ctrl, num_of_slots, &work_LED, 0);
		switch_leds(ctrl, num_of_slots, &work_LED, 1);

		work_LED = 0x01010000;
		writel(work_LED, ctrl->hpc_reg + LED_CONTROL);
		switch_leds(ctrl, num_of_slots, &work_LED, 0);
		switch_leds(ctrl, num_of_slots, &work_LED, 1);
		work_LED = 0x00000101;
		writel(work_LED, ctrl->hpc_reg + LED_CONTROL);
		switch_leds(ctrl, num_of_slots, &work_LED, 0);
		switch_leds(ctrl, num_of_slots, &work_LED, 1);

		work_LED = 0x01010000;
		writel(work_LED, ctrl->hpc_reg + LED_CONTROL);
		for (loop = 0; loop < num_of_slots; loop++) {
			set_SOGO(ctrl);

			/* Wait for SOGO interrupt */
			wait_for_ctrl_irq (ctrl);

			/* Get ready for next iteration */
			long_delay((3*HZ)/10);
			work_LED = work_LED >> 16;
			writel(work_LED, ctrl->hpc_reg + LED_CONTROL);

			set_SOGO(ctrl);

			/* Wait for SOGO interrupt */
			wait_for_ctrl_irq (ctrl);

			/* Get ready for next iteration */
			long_delay((3*HZ)/10);
			work_LED = work_LED << 16;
			writel(work_LED, ctrl->hpc_reg + LED_CONTROL);
			work_LED = work_LED << 1;
			writel(work_LED, ctrl->hpc_reg + LED_CONTROL);
		}

		/* put it back the way it was */
		writel(save_LED, ctrl->hpc_reg + LED_CONTROL);

		set_SOGO(ctrl);

		/* Wait for SOBS to be unset */
		wait_for_ctrl_irq (ctrl);
		break;
	case 2:
		/* Do other stuff here! */
		break;
	case 3:
		/* and more... */
		break;
	}
	return 0;
}