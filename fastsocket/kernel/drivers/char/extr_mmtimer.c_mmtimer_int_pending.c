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
 int HUB_L (unsigned long*) ; 
 scalar_t__ LOCAL_MMR_ADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SH_EVENT_OCCURRED ; 
 int SH_EVENT_OCCURRED_RTC1_INT_MASK ; 

__attribute__((used)) static int mmtimer_int_pending(int comparator)
{
	if (HUB_L((unsigned long *)LOCAL_MMR_ADDR(SH_EVENT_OCCURRED)) &
			SH_EVENT_OCCURRED_RTC1_INT_MASK << comparator)
		return 1;
	else
		return 0;
}