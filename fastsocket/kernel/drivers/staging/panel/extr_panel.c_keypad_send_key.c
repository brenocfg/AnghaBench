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
 size_t KEYPAD_BUFFER ; 
 scalar_t__ init_in_progress ; 
 int /*<<< orphan*/ * keypad_buffer ; 
 size_t keypad_buflen ; 
 scalar_t__ keypad_open_cnt ; 
 int /*<<< orphan*/  keypad_read_wait ; 
 int /*<<< orphan*/  keypad_start ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void keypad_send_key(char *string, int max_len)
{
	if (init_in_progress)
		return;

	/* send the key to the device only if a process is attached to it. */
	if (keypad_open_cnt > 0) {
		while (max_len-- && keypad_buflen < KEYPAD_BUFFER && *string) {
			keypad_buffer[(keypad_start + keypad_buflen++) %
				      KEYPAD_BUFFER] = *string++;
		}
		wake_up_interruptible(&keypad_read_wait);
	}
}