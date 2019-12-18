#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_3__ {int /*<<< orphan*/  quantum_timer_deadline; } ;
typedef  TYPE_1__ cpu_data_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* getCpuDatap () ; 
 scalar_t__ ml_get_interrupts_enabled () ; 
 int /*<<< orphan*/  timer_resync_deadlines () ; 

void
quantum_timer_set_deadline(uint64_t deadline)
{
	cpu_data_t     *cpu_data_ptr;

	/* We should've only come into this path with interrupts disabled */
	assert(ml_get_interrupts_enabled() == FALSE);

	cpu_data_ptr = getCpuDatap();
	cpu_data_ptr->quantum_timer_deadline = deadline;
	timer_resync_deadlines();
}