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
typedef  int /*<<< orphan*/  lapic_timer_mode_t ;
typedef  int lapic_timer_divide_t ;
typedef  int lapic_timer_count_t ;

/* Variables and functions */
 int LAPIC_LVT_PERIODIC ; 
 int LAPIC_READ (int /*<<< orphan*/ ) ; 
 int LAPIC_TIMER_DIVIDE_MASK ; 
 int /*<<< orphan*/  LVT_TIMER ; 
 int /*<<< orphan*/  TIMER_CURRENT_COUNT ; 
 int /*<<< orphan*/  TIMER_DIVIDE_CONFIG ; 
 int /*<<< orphan*/  TIMER_INITIAL_COUNT ; 
 int /*<<< orphan*/  mp_disable_preemption () ; 
 int /*<<< orphan*/  mp_enable_preemption () ; 
 int /*<<< orphan*/  one_shot ; 
 int /*<<< orphan*/  periodic ; 

void
lapic_get_timer(
	lapic_timer_mode_t	*mode,
	lapic_timer_divide_t	*divisor,
	lapic_timer_count_t	*initial_count,
	lapic_timer_count_t	*current_count)
{
	mp_disable_preemption();
	if (mode)
		*mode = (LAPIC_READ(LVT_TIMER) & LAPIC_LVT_PERIODIC) ?
				periodic : one_shot;
	if (divisor)
		*divisor = LAPIC_READ(TIMER_DIVIDE_CONFIG) & LAPIC_TIMER_DIVIDE_MASK;
	if (initial_count)
		*initial_count = LAPIC_READ(TIMER_INITIAL_COUNT);
	if (current_count)
		*current_count = LAPIC_READ(TIMER_CURRENT_COUNT);
	mp_enable_preemption();
}