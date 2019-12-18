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
 int /*<<< orphan*/  poor_mans_delay () ; 
 int /*<<< orphan*/  show_value (unsigned long) ; 

void
panic_handler(unsigned long panicPC, unsigned long panicSSR,
	      unsigned long panicEXPEVT)
{
	while (1) {
		/* This piece of code displays the PC on the LED display */
		show_value(panicPC);
		poor_mans_delay();
		show_value(panicSSR);
		poor_mans_delay();
		show_value(panicEXPEVT);
		poor_mans_delay();
	}
}