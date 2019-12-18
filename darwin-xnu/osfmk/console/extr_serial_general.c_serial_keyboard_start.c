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
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  serial_keyboard_poll () ; 

void
serial_keyboard_start(void)
{
	/* Go see if there are any characters pending now */
	serial_keyboard_poll();
	panic("serial_keyboard_start: we can't get back here\n");
}