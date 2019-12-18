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
 int /*<<< orphan*/  BTN_LEFT ; 
 int /*<<< orphan*/  BTN_MIDDLE ; 
 int /*<<< orphan*/  BTN_RIGHT ; 
 int /*<<< orphan*/  INPORT_CONTROL_PORT ; 
 int /*<<< orphan*/  INPORT_DATA_PORT ; 
 int INPORT_MODE_BASE ; 
 int INPORT_MODE_HOLD ; 
 int INPORT_MODE_IRQ ; 
 int INPORT_REG_BTNS ; 
 int INPORT_REG_MODE ; 
 int INPORT_REG_X ; 
 int INPORT_REG_Y ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  REL_X ; 
 int /*<<< orphan*/  REL_Y ; 
 unsigned char inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inport_dev ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  input_report_rel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t inport_interrupt(int irq, void *dev_id)
{
	unsigned char buttons;

	outb(INPORT_REG_MODE, INPORT_CONTROL_PORT);
	outb(INPORT_MODE_HOLD | INPORT_MODE_IRQ | INPORT_MODE_BASE, INPORT_DATA_PORT);

	outb(INPORT_REG_X, INPORT_CONTROL_PORT);
	input_report_rel(inport_dev, REL_X, inb(INPORT_DATA_PORT));

	outb(INPORT_REG_Y, INPORT_CONTROL_PORT);
	input_report_rel(inport_dev, REL_Y, inb(INPORT_DATA_PORT));

	outb(INPORT_REG_BTNS, INPORT_CONTROL_PORT);
	buttons = inb(INPORT_DATA_PORT);

	input_report_key(inport_dev, BTN_MIDDLE, buttons & 1);
	input_report_key(inport_dev, BTN_LEFT,   buttons & 2);
	input_report_key(inport_dev, BTN_RIGHT,  buttons & 4);

	outb(INPORT_REG_MODE, INPORT_CONTROL_PORT);
	outb(INPORT_MODE_IRQ | INPORT_MODE_BASE, INPORT_DATA_PORT);

	input_sync(inport_dev);
	return IRQ_HANDLED;
}