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
 int /*<<< orphan*/  HMT_low () ; 
 int /*<<< orphan*/  HMT_medium () ; 
 scalar_t__ __USE_RTC () ; 
 unsigned long get_rtcl () ; 
 unsigned long get_tbl () ; 

void __delay(unsigned long loops)
{
	unsigned long start;
	int diff;

	if (__USE_RTC()) {
		start = get_rtcl();
		do {
			/* the RTCL register wraps at 1000000000 */
			diff = get_rtcl() - start;
			if (diff < 0)
				diff += 1000000000;
		} while (diff < loops);
	} else {
		start = get_tbl();
		while (get_tbl() - start < loops)
			HMT_low();
		HMT_medium();
	}
}