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
typedef  int /*<<< orphan*/  u16 ;
struct gtm_timer {int dummy; } ;

/* Variables and functions */
 int gtm_set_ref_timer16 (struct gtm_timer*,int const,int /*<<< orphan*/ ,int) ; 

int gtm_set_exact_timer16(struct gtm_timer *tmr, u16 usec, bool reload)
{
	/* quite obvious, frequency which is enough for µSec precision */
	const int freq = 1000000;

	/*
	 * We can lower the frequency (and probably power consumption) by
	 * dividing both frequency and usec by 2 until there is no remainder.
	 * But we won't bother with this unless savings are measured, so just
	 * run the timer as is.
	 */

	return gtm_set_ref_timer16(tmr, freq, usec, reload);
}