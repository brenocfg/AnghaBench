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
struct wm831x_status {int blink_time; int blink_cyc; int blink; int /*<<< orphan*/  value_lock; int /*<<< orphan*/  work; } ;
struct led_classdev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct wm831x_status* to_wm831x_status (struct led_classdev*) ; 

__attribute__((used)) static int wm831x_status_blink_set(struct led_classdev *led_cdev,
				   unsigned long *delay_on,
				   unsigned long *delay_off)
{
	struct wm831x_status *led = to_wm831x_status(led_cdev);
	unsigned long flags;
	int ret = 0;

	/* Pick some defaults if we've not been given times */
	if (*delay_on == 0 && *delay_off == 0) {
		*delay_on = 250;
		*delay_off = 250;
	}

	spin_lock_irqsave(&led->value_lock, flags);

	/* We only have a limited selection of settings, see if we can
	 * support the configuration we're being given */
	switch (*delay_on) {
	case 1000:
		led->blink_time = 0;
		break;
	case 250:
		led->blink_time = 1;
		break;
	case 125:
		led->blink_time = 2;
		break;
	case 62:
	case 63:
		/* Actually 62.5ms */
		led->blink_time = 3;
		break;
	default:
		ret = -EINVAL;
		break;
	}

	if (ret == 0) {
		switch (*delay_off / *delay_on) {
		case 1:
			led->blink_cyc = 0;
			break;
		case 3:
			led->blink_cyc = 1;
			break;
		case 4:
			led->blink_cyc = 2;
			break;
		case 8:
			led->blink_cyc = 3;
			break;
		default:
			ret = -EINVAL;
			break;
		}
	}

	if (ret == 0)
		led->blink = 1;
	else
		led->blink = 0;

	/* Always update; if we fail turn off blinking since we expect
	 * a software fallback. */
	schedule_work(&led->work);

	spin_unlock_irqrestore(&led->value_lock, flags);

	return ret;
}