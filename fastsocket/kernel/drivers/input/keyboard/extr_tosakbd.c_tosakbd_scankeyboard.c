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
struct tosakbd {int /*<<< orphan*/  lock; int /*<<< orphan*/  timer; int /*<<< orphan*/  input; int /*<<< orphan*/ * keycode; scalar_t__ suspended; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned int GET_ROWS_STATUS (unsigned int) ; 
 int /*<<< orphan*/  KB_ACTIVATE_DELAY ; 
 int /*<<< orphan*/  KB_DISCHARGE_DELAY ; 
 unsigned int KB_ROWMASK (unsigned int) ; 
 unsigned int SCANCODE (unsigned int,unsigned int) ; 
 scalar_t__ SCAN_INTERVAL ; 
 unsigned int TOSA_KEY_SENSE_NUM ; 
 unsigned int TOSA_KEY_STROBE_NUM ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,unsigned int) ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 struct tosakbd* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tosakbd_activate_all () ; 
 int /*<<< orphan*/  tosakbd_activate_col (unsigned int) ; 
 int /*<<< orphan*/  tosakbd_discharge_all () ; 
 int /*<<< orphan*/  tosakbd_reset_col (unsigned int) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tosakbd_scankeyboard(struct platform_device *dev)
{
	struct tosakbd *tosakbd = platform_get_drvdata(dev);
	unsigned int row, col, rowd;
	unsigned long flags;
	unsigned int num_pressed = 0;

	spin_lock_irqsave(&tosakbd->lock, flags);

	if (tosakbd->suspended)
		goto out;

	for (col = 0; col < TOSA_KEY_STROBE_NUM; col++) {
		/*
		 * Discharge the output driver capacitatance
		 * in the keyboard matrix. (Yes it is significant..)
		 */
		tosakbd_discharge_all();
		udelay(KB_DISCHARGE_DELAY);

		tosakbd_activate_col(col);
		udelay(KB_ACTIVATE_DELAY);

		rowd = GET_ROWS_STATUS(col);

		for (row = 0; row < TOSA_KEY_SENSE_NUM; row++) {
			unsigned int scancode, pressed;
			scancode = SCANCODE(row, col);
			pressed = rowd & KB_ROWMASK(row);

			if (pressed && !tosakbd->keycode[scancode])
				dev_warn(&dev->dev,
						"unhandled scancode: 0x%02x\n",
						scancode);

			input_report_key(tosakbd->input,
					tosakbd->keycode[scancode],
					pressed);
			if (pressed)
				num_pressed++;
		}

		tosakbd_reset_col(col);
	}

	tosakbd_activate_all();

	input_sync(tosakbd->input);

	/* if any keys are pressed, enable the timer */
	if (num_pressed)
		mod_timer(&tosakbd->timer, jiffies + SCAN_INTERVAL);

 out:
	spin_unlock_irqrestore(&tosakbd->lock, flags);
}