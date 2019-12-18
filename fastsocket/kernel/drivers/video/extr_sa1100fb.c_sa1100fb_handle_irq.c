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
struct sa1100fb_info {int /*<<< orphan*/  ctrlr_wait; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  LCCR0 ; 
 int /*<<< orphan*/  LCCR0_LDM ; 
 unsigned int LCSR ; 
 unsigned int LCSR_LDD ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t sa1100fb_handle_irq(int irq, void *dev_id)
{
	struct sa1100fb_info *fbi = dev_id;
	unsigned int lcsr = LCSR;

	if (lcsr & LCSR_LDD) {
		LCCR0 |= LCCR0_LDM;
		wake_up(&fbi->ctrlr_wait);
	}

	LCSR = lcsr;
	return IRQ_HANDLED;
}