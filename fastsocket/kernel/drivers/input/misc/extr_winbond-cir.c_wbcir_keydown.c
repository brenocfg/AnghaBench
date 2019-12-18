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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct wbcir_data {scalar_t__ last_scancode; scalar_t__ last_toggle; int keypressed; unsigned int last_keycode; scalar_t__ keyup_jiffies; int /*<<< orphan*/  timer_keyup; int /*<<< orphan*/  rxtrigger; int /*<<< orphan*/  input_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_MSC ; 
 int /*<<< orphan*/  IR_KEYPRESS_TIMEOUT ; 
 unsigned int KEY_RESERVED ; 
 int /*<<< orphan*/  LED_FULL ; 
 int /*<<< orphan*/  LED_OFF ; 
 int /*<<< orphan*/  MSC_SCAN ; 
 int /*<<< orphan*/  input_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,unsigned int,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  led_trigger_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 unsigned int wbcir_do_getkeycode (struct wbcir_data*,scalar_t__) ; 

__attribute__((used)) static void
wbcir_keydown(struct wbcir_data *data, u32 scancode, u8 toggle)
{
	unsigned int keycode;

	/* Repeat? */
	if (data->last_scancode == scancode &&
	    data->last_toggle == toggle &&
	    data->keypressed)
		goto set_timer;
	data->last_scancode = scancode;

	/* Do we need to release an old keypress? */
	if (data->keypressed) {
		input_report_key(data->input_dev, data->last_keycode, 0);
		input_sync(data->input_dev);
		data->keypressed = 0;
	}

	/* Report scancode */
	input_event(data->input_dev, EV_MSC, MSC_SCAN, (int)scancode);

	/* Do we know this scancode? */
	keycode = wbcir_do_getkeycode(data, scancode);
	if (keycode == KEY_RESERVED)
		goto set_timer;

	/* Register a keypress */
	input_report_key(data->input_dev, keycode, 1);
	data->keypressed = 1;
	data->last_keycode = keycode;
	data->last_toggle = toggle;

set_timer:
	input_sync(data->input_dev);
	led_trigger_event(data->rxtrigger,
			  data->keypressed ? LED_FULL : LED_OFF);
	data->keyup_jiffies = jiffies + msecs_to_jiffies(IR_KEYPRESS_TIMEOUT);
	mod_timer(&data->timer_keyup, data->keyup_jiffies);
}