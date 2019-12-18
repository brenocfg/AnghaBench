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
typedef  int u32 ;

/* Variables and functions */
 int KBD_THREAD_KBD_SCAN_INTERVAL ; 
 int /*<<< orphan*/  KBD_THREAD_UDELAY ; 
 int /*<<< orphan*/  USBKeyboard_IsConnected () ; 
 int /*<<< orphan*/  USBKeyboard_Scan () ; 
 int /*<<< orphan*/  _kbd_scan_for_keyboard () ; 
 int /*<<< orphan*/  _kbd_thread_quit ; 
 int /*<<< orphan*/  usleep (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void * _kbd_thread_func(void *arg) {
	u32 turns = 0;

	while (!_kbd_thread_quit) {
		// scan for new attached keyboards
		if ((turns % KBD_THREAD_KBD_SCAN_INTERVAL) == 0) {
			if (!USBKeyboard_IsConnected())
				_kbd_scan_for_keyboard();

			turns = 0;
		}
		turns++;

		USBKeyboard_Scan();
		usleep(KBD_THREAD_UDELAY);
	}

	return NULL;
}