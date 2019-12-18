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
 unsigned char AUXIO_LED ; 
 unsigned char get_auxio () ; 
 int /*<<< orphan*/  set_auxio (unsigned char,unsigned char) ; 

__attribute__((used)) static inline void led_toggle(void)
{
	unsigned char val = get_auxio();
	unsigned char on, off;

	if (val & AUXIO_LED) {
		on = 0;
		off = AUXIO_LED;
	} else {
		on = AUXIO_LED;
		off = 0;
	}

	set_auxio(on, off);
}