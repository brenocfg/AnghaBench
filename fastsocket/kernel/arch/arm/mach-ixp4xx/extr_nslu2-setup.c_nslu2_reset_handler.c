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
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  machine_power_off () ; 

__attribute__((used)) static irqreturn_t nslu2_reset_handler(int irq, void *dev_id)
{
	/* This is the paper-clip reset, it shuts the machine down directly.
	 */
	machine_power_off();

	return IRQ_HANDLED;
}