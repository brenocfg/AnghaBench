#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct bintime {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_adj_nsx; int /*<<< orphan*/  s_scale_ns; int /*<<< orphan*/  tick_scale_x; scalar_t__ offset_count; } ;

/* Variables and functions */
 TYPE_1__ clock_calend ; 
 struct bintime scale_delta (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct bintime
get_scaled_time(uint64_t now)
{
	uint64_t delta;

	/*
	 * Compute ticks elapsed since last scale update.
	 * This time will be scaled according to the value given by ntp kern.
	 */
	delta = now - clock_calend.offset_count;

	return scale_delta(delta, clock_calend.tick_scale_x, clock_calend.s_scale_ns, clock_calend.s_adj_nsx);
}