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
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 unsigned char MK712_CONVERSION_COMPLETE ; 
 scalar_t__ MK712_STATUS ; 
 unsigned char MK712_STATUS_TOUCH ; 
 scalar_t__ MK712_X ; 
 scalar_t__ MK712_Y ; 
 unsigned char inb (scalar_t__) ; 
 int /*<<< orphan*/  input_report_abs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned short) ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 int inw (scalar_t__) ; 
 int /*<<< orphan*/  mk712_dev ; 
 scalar_t__ mk712_io ; 
 int /*<<< orphan*/  mk712_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t mk712_interrupt(int irq, void *dev_id)
{
	unsigned char status;
	static int debounce = 1;
	static unsigned short last_x;
	static unsigned short last_y;

	spin_lock(&mk712_lock);

	status = inb(mk712_io + MK712_STATUS);

	if (~status & MK712_CONVERSION_COMPLETE) {
		debounce = 1;
		goto end;
	}

	if (~status & MK712_STATUS_TOUCH) {
		debounce = 1;
		input_report_key(mk712_dev, BTN_TOUCH, 0);
		goto end;
	}

	if (debounce) {
		debounce = 0;
		goto end;
	}

	input_report_key(mk712_dev, BTN_TOUCH, 1);
	input_report_abs(mk712_dev, ABS_X, last_x);
	input_report_abs(mk712_dev, ABS_Y, last_y);

 end:
	last_x = inw(mk712_io + MK712_X) & 0x0fff;
	last_y = inw(mk712_io + MK712_Y) & 0x0fff;
	input_sync(mk712_dev);
	spin_unlock(&mk712_lock);
	return IRQ_HANDLED;
}