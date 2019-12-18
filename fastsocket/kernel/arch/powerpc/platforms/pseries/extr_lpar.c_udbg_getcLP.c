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
 int udbg_getc_pollLP () ; 

__attribute__((used)) static int udbg_getcLP(void)
{
	int ch;
	for (;;) {
		ch = udbg_getc_pollLP();
		if (ch == -1) {
			/* This shouldn't be needed...but... */
			volatile unsigned long delay;
			for (delay=0; delay < 2000000; delay++)
				;
		} else {
			return ch;
		}
	}
}