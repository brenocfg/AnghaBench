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
struct spitzkbd {int /*<<< orphan*/  lock; int /*<<< orphan*/  timer; int /*<<< orphan*/  input; scalar_t__ suspend_jiffies; int /*<<< orphan*/ * keycode; scalar_t__ suspended; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_PWR ; 
 int GPIO_bit (int /*<<< orphan*/ ) ; 
 int GPLR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KB_ACTIVATE_DELAY ; 
 unsigned int KB_COLS ; 
 int /*<<< orphan*/  KB_DISCHARGE_DELAY ; 
 unsigned int KB_ROWMASK (unsigned int) ; 
 unsigned int KB_ROWS ; 
 int /*<<< orphan*/  KEY_SUSPEND ; 
 unsigned int SCANCODE (unsigned int,unsigned int) ; 
 int SCAN_INTERVAL ; 
 int /*<<< orphan*/  SPITZ_GPIO_ON_KEY ; 
 int /*<<< orphan*/  SPITZ_GPIO_SYNC ; 
 int /*<<< orphan*/  SPITZ_KEY_SYNC ; 
 int /*<<< orphan*/  input_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spitzkbd_activate_all () ; 
 int /*<<< orphan*/  spitzkbd_activate_col (unsigned int) ; 
 int /*<<< orphan*/  spitzkbd_discharge_all () ; 
 unsigned int spitzkbd_get_row_status (unsigned int) ; 
 int /*<<< orphan*/  spitzkbd_reset_col (unsigned int) ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void spitzkbd_scankeyboard(struct spitzkbd *spitzkbd_data)
{
	unsigned int row, col, rowd;
	unsigned long flags;
	unsigned int num_pressed, pwrkey = ((GPLR(SPITZ_GPIO_ON_KEY) & GPIO_bit(SPITZ_GPIO_ON_KEY)) != 0);

	if (spitzkbd_data->suspended)
		return;

	spin_lock_irqsave(&spitzkbd_data->lock, flags);

	num_pressed = 0;
	for (col = 0; col < KB_COLS; col++) {
		/*
		 * Discharge the output driver capacitatance
		 * in the keyboard matrix. (Yes it is significant..)
		 */

		spitzkbd_discharge_all();
		udelay(KB_DISCHARGE_DELAY);

		spitzkbd_activate_col(col);
		udelay(KB_ACTIVATE_DELAY);

		rowd = spitzkbd_get_row_status(col);
		for (row = 0; row < KB_ROWS; row++) {
			unsigned int scancode, pressed;

			scancode = SCANCODE(row, col);
			pressed = rowd & KB_ROWMASK(row);

			input_report_key(spitzkbd_data->input, spitzkbd_data->keycode[scancode], pressed);

			if (pressed)
				num_pressed++;
		}
		spitzkbd_reset_col(col);
	}

	spitzkbd_activate_all();

	input_report_key(spitzkbd_data->input, SPITZ_KEY_SYNC, (GPLR(SPITZ_GPIO_SYNC) & GPIO_bit(SPITZ_GPIO_SYNC)) != 0 );
	input_report_key(spitzkbd_data->input, KEY_SUSPEND, pwrkey);

	if (pwrkey && time_after(jiffies, spitzkbd_data->suspend_jiffies + msecs_to_jiffies(1000))) {
		input_event(spitzkbd_data->input, EV_PWR, KEY_SUSPEND, 1);
		spitzkbd_data->suspend_jiffies = jiffies;
	}

	input_sync(spitzkbd_data->input);

	/* if any keys are pressed, enable the timer */
	if (num_pressed)
		mod_timer(&spitzkbd_data->timer, jiffies + msecs_to_jiffies(SCAN_INTERVAL));

	spin_unlock_irqrestore(&spitzkbd_data->lock, flags);
}