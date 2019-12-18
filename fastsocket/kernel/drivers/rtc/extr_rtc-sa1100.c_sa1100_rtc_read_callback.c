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
struct device {int dummy; } ;

/* Variables and functions */
 unsigned long OSCR ; 
 unsigned long OSMR1 ; 
 int /*<<< orphan*/  OSSR ; 
 int /*<<< orphan*/  OSSR_M1 ; 
 int RTC_PF ; 
 unsigned long rtc_freq ; 
 unsigned long timer_freq ; 

__attribute__((used)) static int sa1100_rtc_read_callback(struct device *dev, int data)
{
	if (data & RTC_PF) {
		/* interpolate missed periods and set match for the next */
		unsigned long period = timer_freq / rtc_freq;
		unsigned long oscr = OSCR;
		unsigned long osmr1 = OSMR1;
		unsigned long missed = (oscr - osmr1)/period;
		data += missed << 8;
		OSSR = OSSR_M1;	/* clear match on timer 1 */
		OSMR1 = osmr1 + (missed + 1)*period;
		/* Ensure we didn't miss another match in the mean time.
		 * Here we compare (match - OSCR) 8 instead of 0 --
		 * see comment in pxa_timer_interrupt() for explanation.
		 */
		while( (signed long)((osmr1 = OSMR1) - OSCR) <= 8 ) {
			data += 0x100;
			OSSR = OSSR_M1;	/* clear match on timer 1 */
			OSMR1 = osmr1 + period;
		}
	}
	return data;
}