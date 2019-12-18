#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct clocksource {int dummy; } ;
typedef  int /*<<< orphan*/  cycle_t ;
struct TYPE_4__ {int /*<<< orphan*/  cycle_last; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* get_cycle_counter ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  VMI_CYCLES_REAL ; 
 TYPE_2__ clocksource_vmi ; 
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 TYPE_1__ vmi_timer_ops ; 

__attribute__((used)) static cycle_t read_real_cycles(struct clocksource *cs)
{
	cycle_t ret = (cycle_t)vmi_timer_ops.get_cycle_counter(VMI_CYCLES_REAL);
	return max(ret, clocksource_vmi.cycle_last);
}