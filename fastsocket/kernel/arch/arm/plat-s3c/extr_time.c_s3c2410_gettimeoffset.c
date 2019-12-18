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
 int /*<<< orphan*/  S3C2410_TCNTO (int) ; 
 unsigned long __raw_readl (int /*<<< orphan*/ ) ; 
 scalar_t__ s3c24xx_ostimer_pending () ; 
 unsigned long timer_startval ; 
 unsigned long timer_ticks_to_usec (unsigned long) ; 

__attribute__((used)) static unsigned long s3c2410_gettimeoffset (void)
{
	unsigned long tdone;
	unsigned long tval;

	/* work out how many ticks have gone since last timer interrupt */

	tval =  __raw_readl(S3C2410_TCNTO(4));
	tdone = timer_startval - tval;

	/* check to see if there is an interrupt pending */

	if (s3c24xx_ostimer_pending()) {
		/* re-read the timer, and try and fix up for the missed
		 * interrupt. Note, the interrupt may go off before the
		 * timer has re-loaded from wrapping.
		 */

		tval =  __raw_readl(S3C2410_TCNTO(4));
		tdone = timer_startval - tval;

		if (tval != 0)
			tdone += timer_startval;
	}

	return timer_ticks_to_usec(tdone);
}