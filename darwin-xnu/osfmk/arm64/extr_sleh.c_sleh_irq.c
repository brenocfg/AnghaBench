#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* interrupt_handler ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  interrupt_source; int /*<<< orphan*/  interrupt_nub; int /*<<< orphan*/  interrupt_refCon; int /*<<< orphan*/  interrupt_target; } ;
typedef  TYPE_1__ cpu_data_t ;
typedef  int /*<<< orphan*/  arm_saved_state_t ;
struct TYPE_5__ {int* index_ptr; int* buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_INTR_TYPE_OTHER ; 
 size_t ENTROPY_BUFFER_SIZE ; 
 TYPE_3__ EntropyData ; 
 int __ror (int,int) ; 
 TYPE_1__* getCpuDatap () ; 
 int get_preemption_level () ; 
 scalar_t__ ml_get_timebase () ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/  (*) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ),int,int) ; 
 int /*<<< orphan*/  sleh_interrupt_handler_epilogue () ; 
 int /*<<< orphan*/  sleh_interrupt_handler_prologue (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
sleh_irq(arm_saved_state_t *state)
{
	uint64_t     timestamp            = 0;
	uint32_t     old_entropy_data     = 0;
	uint32_t *   old_entropy_data_ptr = NULL;
	uint32_t *   new_entropy_data_ptr = NULL;
	cpu_data_t * cdp                  = getCpuDatap();
#if DEVELOPMENT || DEBUG
	int preemption_level = get_preemption_level();
#endif

	sleh_interrupt_handler_prologue(state, DBG_INTR_TYPE_OTHER);

	/* Run the registered interrupt handler. */
	cdp->interrupt_handler(cdp->interrupt_target,
	                       cdp->interrupt_refCon,
	                       cdp->interrupt_nub,
	                       cdp->interrupt_source);

	/* We use interrupt timing as an entropy source. */
	timestamp = ml_get_timebase();

	/*
	 * The buffer index is subject to races, but as these races should only
	 * result in multiple CPUs updating the same location, the end result
	 * should be that noise gets written into the entropy buffer.  As this
	 * is the entire point of the entropy buffer, we will not worry about
	 * these races for now.
	 */
	old_entropy_data_ptr = EntropyData.index_ptr;
	new_entropy_data_ptr = old_entropy_data_ptr + 1;

	if (new_entropy_data_ptr >= &EntropyData.buffer[ENTROPY_BUFFER_SIZE]) {
		new_entropy_data_ptr = EntropyData.buffer;
	}

	EntropyData.index_ptr = new_entropy_data_ptr;

	/* Mix the timestamp data and the old data together. */
	old_entropy_data = *old_entropy_data_ptr;
	*old_entropy_data_ptr = (uint32_t)timestamp ^ __ror(old_entropy_data, 9);

	sleh_interrupt_handler_epilogue();
#if DEVELOPMENT || DEBUG
	if (preemption_level != get_preemption_level())
		panic("irq handler %p changed preemption level from %d to %d", cdp->interrupt_handler, preemption_level, get_preemption_level());
#endif
}