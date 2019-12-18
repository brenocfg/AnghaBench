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
 unsigned long get_timestamp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 scalar_t__ softlockup_thresh ; 
 scalar_t__ time_after (unsigned long,scalar_t__) ; 

__attribute__((used)) static int is_softlockup(unsigned long touch_ts)
{
	unsigned long now = get_timestamp(smp_processor_id());

	/* Warn about unreasonable delays: */
	if (time_after(now, touch_ts + softlockup_thresh))
		return now - touch_ts;

	return 0;
}