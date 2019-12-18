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

/* Variables and functions */
 int /*<<< orphan*/  init_scan_timer () ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 scalar_t__ keypad_buflen ; 
 int keypad_initialized ; 
 scalar_t__*** keypad_profile ; 
 int /*<<< orphan*/  keypad_read_wait ; 
 int /*<<< orphan*/  panel_bind_key (scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*) ; 

__attribute__((used)) static void keypad_init(void)
{
	int keynum;
	init_waitqueue_head(&keypad_read_wait);
	keypad_buflen = 0;	/* flushes any eventual noisy keystroke */

	/* Let's create all known keys */

	for (keynum = 0; keypad_profile[keynum][0][0]; keynum++) {
		panel_bind_key(keypad_profile[keynum][0],
			       keypad_profile[keynum][1],
			       keypad_profile[keynum][2],
			       keypad_profile[keynum][3]);
	}

	init_scan_timer();
	keypad_initialized = 1;
}