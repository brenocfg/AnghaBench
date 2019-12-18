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
 int /*<<< orphan*/  MN10300_TSCCLK ; 
 long TMTSCBC ; 
 long __muldiv64u (unsigned long,int /*<<< orphan*/ ,int) ; 

void __udelay(unsigned long usecs)
{
	signed long ioclk, stop;

	/* usecs * CLK / 1E6 */
	stop = __muldiv64u(usecs, MN10300_TSCCLK, 1000000);
	stop = TMTSCBC - stop;

	do {
		ioclk = TMTSCBC;
	} while (stop < ioclk);
}