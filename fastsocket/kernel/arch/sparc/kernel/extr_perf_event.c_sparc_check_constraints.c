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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int PIC_LOWER ; 
 int PIC_UPPER ; 
 int /*<<< orphan*/  perf_event_decode (unsigned long,int /*<<< orphan*/ *,int*) ; 
 int perf_max_events ; 

__attribute__((used)) static int sparc_check_constraints(unsigned long *events, int n_ev)
{
	if (n_ev <= perf_max_events) {
		u8 msk1, msk2;
		u16 dummy;

		if (n_ev == 1)
			return 0;
		BUG_ON(n_ev != 2);
		perf_event_decode(events[0], &dummy, &msk1);
		perf_event_decode(events[1], &dummy, &msk2);

		/* If both events can go on any counter, OK.  */
		if (msk1 == (PIC_UPPER | PIC_LOWER) &&
		    msk2 == (PIC_UPPER | PIC_LOWER))
			return 0;

		/* If one event is limited to a specific counter,
		 * and the other can go on both, OK.
		 */
		if ((msk1 == PIC_UPPER || msk1 == PIC_LOWER) &&
		    msk2 == (PIC_UPPER | PIC_LOWER))
			return 0;
		if ((msk2 == PIC_UPPER || msk2 == PIC_LOWER) &&
		    msk1 == (PIC_UPPER | PIC_LOWER))
			return 0;

		/* If the events are fixed to different counters, OK.  */
		if ((msk1 == PIC_UPPER && msk2 == PIC_LOWER) ||
		    (msk1 == PIC_LOWER && msk2 == PIC_UPPER))
			return 0;

		/* Otherwise, there is a conflict.  */
	}

	return -1;
}