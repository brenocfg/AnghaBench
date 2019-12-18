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
 int NSEC_PER_SEC ; 
 int softlockup_thresh ; 

__attribute__((used)) static unsigned long get_sample_period(void)
{
	/*
	 * convert softlockup_thresh from seconds to ns
	 * the divide by 5 is to give hrtimer 5 chances to
	 * increment before the hardlockup detector generates
	 * a warning
	 */
	return softlockup_thresh / 5 * NSEC_PER_SEC;
}