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
typedef  int lapic_timer_count_t ;

/* Variables and functions */
 int LAPIC_LVT_MASKED ; 
 int LAPIC_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LAPIC_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LVT_TIMER ; 
 int /*<<< orphan*/  TIMER_INITIAL_COUNT ; 

void
lapic_set_timer_fast(
	lapic_timer_count_t	initial_count)
{
	LAPIC_WRITE(LVT_TIMER, LAPIC_READ(LVT_TIMER) & ~LAPIC_LVT_MASKED);
	LAPIC_WRITE(TIMER_INITIAL_COUNT, initial_count);
}