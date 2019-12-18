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
struct input_handle {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned int EV_KEY ; 
 unsigned int EV_MSC ; 
 scalar_t__ HW_RAW (int /*<<< orphan*/ ) ; 
 unsigned int MSC_RAW ; 
 int do_poke_blanked_console ; 
 int /*<<< orphan*/  kbd_keycode (unsigned int,int,scalar_t__) ; 
 int /*<<< orphan*/  kbd_rawcode (int) ; 
 int /*<<< orphan*/  keyboard_tasklet ; 
 int /*<<< orphan*/  schedule_console_callback () ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void kbd_event(struct input_handle *handle, unsigned int event_type,
		      unsigned int event_code, int value)
{
	if (event_type == EV_MSC && event_code == MSC_RAW && HW_RAW(handle->dev))
		kbd_rawcode(value);
	if (event_type == EV_KEY)
		kbd_keycode(event_code, value, HW_RAW(handle->dev));
	tasklet_schedule(&keyboard_tasklet);
	do_poke_blanked_console = 1;
	schedule_console_callback();
}