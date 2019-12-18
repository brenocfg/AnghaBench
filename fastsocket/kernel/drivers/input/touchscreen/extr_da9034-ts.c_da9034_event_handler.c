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
struct da9034_touch {int state; int /*<<< orphan*/  interval_ms; int /*<<< orphan*/  tsi_work; } ;

/* Variables and functions */
 int EVENT_PEN_DOWN ; 
 int EVENT_PEN_UP ; 
 int EVENT_TIMEDOUT ; 
 int EVENT_TSI_READY ; 
#define  STATE_BUSY 131 
#define  STATE_IDLE 130 
#define  STATE_STOP 129 
#define  STATE_WAIT 128 
 int /*<<< orphan*/  detect_pen_down (struct da9034_touch*,int) ; 
 int /*<<< orphan*/  is_pen_down (struct da9034_touch*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int read_tsi (struct da9034_touch*) ; 
 int /*<<< orphan*/  report_pen_down (struct da9034_touch*) ; 
 int /*<<< orphan*/  report_pen_up (struct da9034_touch*) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int start_tsi (struct da9034_touch*) ; 
 int stop_tsi (struct da9034_touch*) ; 

__attribute__((used)) static void da9034_event_handler(struct da9034_touch *touch, int event)
{
	int err;

	switch (touch->state) {
	case STATE_IDLE:
		if (event != EVENT_PEN_DOWN)
			break;

		/* Enable auto measurement of the TSI, this will
		 * automatically disable pen down detection
		 */
		err = start_tsi(touch);
		if (err)
			goto err_reset;

		touch->state = STATE_BUSY;
		break;

	case STATE_BUSY:
		if (event != EVENT_TSI_READY)
			break;

		err = read_tsi(touch);
		if (err)
			goto err_reset;

		/* Disable auto measurement of the TSI, so that
		 * pen down status will be available
		 */
		err = stop_tsi(touch);
		if (err)
			goto err_reset;

		touch->state = STATE_STOP;

		/* FIXME: PEN_{UP/DOWN} events are expected to be
		 * available by stopping TSI, but this is found not
		 * always true, delay and simulate such an event
		 * here is more reliable
		 */
		mdelay(1);
		da9034_event_handler(touch,
				     is_pen_down(touch) ? EVENT_PEN_DOWN :
							  EVENT_PEN_UP);
		break;

	case STATE_STOP:
		if (event == EVENT_PEN_DOWN) {
			report_pen_down(touch);
			schedule_delayed_work(&touch->tsi_work,
				msecs_to_jiffies(touch->interval_ms));
			touch->state = STATE_WAIT;
		}

		if (event == EVENT_PEN_UP) {
			report_pen_up(touch);
			touch->state = STATE_IDLE;
		}
		break;

	case STATE_WAIT:
		if (event != EVENT_TIMEDOUT)
			break;

		if (is_pen_down(touch)) {
			start_tsi(touch);
			touch->state = STATE_BUSY;
		} else {
			report_pen_up(touch);
			touch->state = STATE_IDLE;
		}
		break;
	}
	return;

err_reset:
	touch->state = STATE_IDLE;
	stop_tsi(touch);
	detect_pen_down(touch, 1);
}