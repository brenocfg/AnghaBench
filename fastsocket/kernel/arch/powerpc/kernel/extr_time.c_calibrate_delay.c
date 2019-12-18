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
 int /*<<< orphan*/  loops_per_jiffy ; 
 int /*<<< orphan*/  tb_ticks_per_jiffy ; 

void calibrate_delay(void)
{
	/* Some generic code (such as spinlock debug) use loops_per_jiffy
	 * as the number of __delay(1) in a jiffy, so make it so
	 */
	loops_per_jiffy = tb_ticks_per_jiffy;
}