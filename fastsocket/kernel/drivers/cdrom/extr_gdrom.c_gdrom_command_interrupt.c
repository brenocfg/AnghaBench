#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int pending; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  GDROM_STATUSCOMMAND_REG ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  command_queue ; 
 int /*<<< orphan*/  ctrl_inb (int /*<<< orphan*/ ) ; 
 TYPE_1__ gd ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t gdrom_command_interrupt(int irq, void *dev_id)
{
	gd.status = ctrl_inb(GDROM_STATUSCOMMAND_REG);
	if (gd.pending != 1)
		return IRQ_HANDLED;
	gd.pending = 0;
	wake_up_interruptible(&command_queue);
	return IRQ_HANDLED;
}