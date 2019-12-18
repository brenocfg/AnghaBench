#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ type; int /*<<< orphan*/  symbol; } ;
typedef  TYPE_1__ keyboard_event ;
struct TYPE_5__ {int tail; int head; int /*<<< orphan*/ * buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  KBD_THREAD_UDELAY ; 
 scalar_t__ KEYBOARD_GetEvent (TYPE_1__*) ; 
 scalar_t__ KEYBOARD_PRESSED ; 
 int /*<<< orphan*/  _kbd_thread_quit ; 
 TYPE_2__ _keyBuffer ; 
 int /*<<< orphan*/  usleep (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void * _kbd_buf_thread_func(void *arg) {
	keyboard_event event;
	while (!_kbd_thread_quit) {
		if (((_keyBuffer.tail+1)&255) != _keyBuffer.head) {
			if ( KEYBOARD_GetEvent(&event)) {
				if (event.type == KEYBOARD_PRESSED) {
					_keyBuffer.buf[_keyBuffer.tail] = event.symbol;
					_keyBuffer.tail++;
				}
			}
		}
		usleep(KBD_THREAD_UDELAY);
	}
	return NULL;
}