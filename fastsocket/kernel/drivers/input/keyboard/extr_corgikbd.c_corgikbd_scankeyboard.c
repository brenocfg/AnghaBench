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
struct corgikbd {scalar_t__* keycode; int /*<<< orphan*/  lock; int /*<<< orphan*/  timer; int /*<<< orphan*/  input; scalar_t__ suspend_jiffies; scalar_t__ suspended; } ;

/* Variables and functions */
 scalar_t__ CORGI_KEY_OFF ; 
 int /*<<< orphan*/  EV_PWR ; 
 unsigned int GET_ROWS_STATUS (unsigned int) ; 
 scalar_t__ HZ ; 
 int /*<<< orphan*/  KB_ACTIVATE_DELAY ; 
 unsigned int KB_COLS ; 
 int /*<<< orphan*/  KB_DISCHARGE_DELAY ; 
 unsigned int KB_ROWMASK (unsigned int) ; 
 unsigned int KB_ROWS ; 
 unsigned int SCANCODE (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  SCAN_INTERVAL ; 
 int /*<<< orphan*/  corgikbd_activate_all () ; 
 int /*<<< orphan*/  corgikbd_activate_col (unsigned int) ; 
 int /*<<< orphan*/  corgikbd_discharge_all () ; 
 int /*<<< orphan*/  corgikbd_reset_col (unsigned int) ; 
 int /*<<< orphan*/  input_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void corgikbd_scankeyboard(struct corgikbd *corgikbd_data)
{
	unsigned int row, col, rowd;
	unsigned long flags;
	unsigned int num_pressed;

	if (corgikbd_data->suspended)
		return;

	spin_lock_irqsave(&corgikbd_data->lock, flags);

	num_pressed = 0;
	for (col = 0; col < KB_COLS; col++) {
		/*
		 * Discharge the output driver capacitatance
		 * in the keyboard matrix. (Yes it is significant..)
		 */

		corgikbd_discharge_all();
		udelay(KB_DISCHARGE_DELAY);

		corgikbd_activate_col(col);
		udelay(KB_ACTIVATE_DELAY);

		rowd = GET_ROWS_STATUS(col);
		for (row = 0; row < KB_ROWS; row++) {
			unsigned int scancode, pressed;

			scancode = SCANCODE(row, col);
			pressed = rowd & KB_ROWMASK(row);

			input_report_key(corgikbd_data->input, corgikbd_data->keycode[scancode], pressed);

			if (pressed)
				num_pressed++;

			if (pressed && (corgikbd_data->keycode[scancode] == CORGI_KEY_OFF)
					&& time_after(jiffies, corgikbd_data->suspend_jiffies + HZ)) {
				input_event(corgikbd_data->input, EV_PWR, CORGI_KEY_OFF, 1);
				corgikbd_data->suspend_jiffies=jiffies;
			}
		}
		corgikbd_reset_col(col);
	}

	corgikbd_activate_all();

	input_sync(corgikbd_data->input);

	/* if any keys are pressed, enable the timer */
	if (num_pressed)
		mod_timer(&corgikbd_data->timer, jiffies + msecs_to_jiffies(SCAN_INTERVAL));

	spin_unlock_irqrestore(&corgikbd_data->lock, flags);
}