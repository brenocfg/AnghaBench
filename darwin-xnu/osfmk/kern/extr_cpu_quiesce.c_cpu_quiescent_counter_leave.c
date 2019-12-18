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
typedef  TYPE_1__* processor_t ;
typedef  int checkin_mask_t ;
struct TYPE_3__ {int cpu_id; scalar_t__ cpu_quiesce_state; int /*<<< orphan*/  cpu_quiesce_last_checkin; } ;

/* Variables and functions */
 int /*<<< orphan*/  AST_UNQUIESCE ; 
 scalar_t__ CPU_QUIESCE_COUNTER_JOINED ; 
 void* CPU_QUIESCE_COUNTER_LEFT ; 
 scalar_t__ CPU_QUIESCE_COUNTER_PENDING_JOIN ; 
 int /*<<< orphan*/  acq_rel ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ast_off (int /*<<< orphan*/ ) ; 
 int cpu_checked_in_bit (int) ; 
 int cpu_expected_bit (int) ; 
 int /*<<< orphan*/  cpu_quiescent_counter_commit (int /*<<< orphan*/ ) ; 
 scalar_t__ cpu_quiescent_counter_needs_commit (int) ; 
 int /*<<< orphan*/  cpu_quiescing_checkin_state ; 
 TYPE_1__* current_processor () ; 
 int os_atomic_and_orig (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

void
cpu_quiescent_counter_leave(uint64_t ctime)
{
	processor_t processor = current_processor();
	int cpuid = processor->cpu_id;

	assert(processor->cpu_quiesce_state == CPU_QUIESCE_COUNTER_JOINED ||
	       processor->cpu_quiesce_state == CPU_QUIESCE_COUNTER_PENDING_JOIN);

	/* We no longer need the cpu_quiescent_counter_ast callback to be armed */
	ast_off(AST_UNQUIESCE);

	if (processor->cpu_quiesce_state == CPU_QUIESCE_COUNTER_PENDING_JOIN) {
		/* We never actually joined, so we don't have to do the work to leave. */
		processor->cpu_quiesce_state = CPU_QUIESCE_COUNTER_LEFT;
		return;
	}

	/* Leaving can't be deferred, even if we're within the min interval */
	processor->cpu_quiesce_last_checkin = ctime;

	checkin_mask_t mask = cpu_checked_in_bit(cpuid) | cpu_expected_bit(cpuid);

	checkin_mask_t orig_state = os_atomic_and_orig(&cpu_quiescing_checkin_state,
	                                               ~mask, acq_rel);

	assert((orig_state & cpu_expected_bit(cpuid)));

	processor->cpu_quiesce_state = CPU_QUIESCE_COUNTER_LEFT;

	if (cpu_quiescent_counter_needs_commit(orig_state)) {
		/*
		 * the old state indicates someone else was already doing a commit
		 * but hadn't finished yet.  We successfully inserted the acq_rel
		 * before they finished the commit by resetting the bitfield,
		 * so we're done here.
		 */
		return;
	}

	checkin_mask_t new_state = orig_state & ~mask;

	if (cpu_quiescent_counter_needs_commit(new_state)) {
		cpu_quiescent_counter_commit(ctime);
	}
}