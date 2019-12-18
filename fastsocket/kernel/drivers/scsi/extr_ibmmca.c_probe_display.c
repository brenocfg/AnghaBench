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
 int LED_DISP ; 
 scalar_t__ MOD95_LED_PORT ; 
 int display_mode ; 
 int /*<<< orphan*/  outb (char,scalar_t__) ; 
 int /*<<< orphan*/  outl (int,scalar_t__) ; 

__attribute__((used)) static int probe_display(int what)
{
	static int rotator = 0;
	const char rotor[] = "|/-\\";

	if (!(display_mode & LED_DISP))
		return 0;
	if (!what) {
		outl(0x20202020, MOD95_LED_PORT);
		outl(0x20202020, MOD95_LED_PORT + 4);
	} else {
		outb('S', MOD95_LED_PORT + 7);
		outb('C', MOD95_LED_PORT + 6);
		outb('S', MOD95_LED_PORT + 5);
		outb('I', MOD95_LED_PORT + 4);
		outb('i', MOD95_LED_PORT + 3);
		outb('n', MOD95_LED_PORT + 2);
		outb('i', MOD95_LED_PORT + 1);
		outb((char) (rotor[rotator]), MOD95_LED_PORT);
		rotator++;
		if (rotator > 3)
			rotator = 0;
	}
	return 0;
}