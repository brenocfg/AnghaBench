#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_shared_region_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_4__ {scalar_t__ sr_ref_count; int /*<<< orphan*/ * sr_timer_call; } ;

/* Variables and functions */
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int /*<<< orphan*/  SHARED_REGION_TRACE_DEBUG (char*) ; 
 scalar_t__ VM_KERNEL_ADDRPERM (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ thread_call_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread_call_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_shared_region_lock ; 

__attribute__((used)) static void
vm_shared_region_reference_locked(
	vm_shared_region_t	shared_region)
{
	LCK_MTX_ASSERT(&vm_shared_region_lock, LCK_MTX_ASSERT_OWNED);

	SHARED_REGION_TRACE_DEBUG(
		("shared_region: -> reference_locked(%p)\n",
		 (void *)VM_KERNEL_ADDRPERM(shared_region)));
	assert(shared_region->sr_ref_count > 0);
	shared_region->sr_ref_count++;

	if (shared_region->sr_timer_call != NULL) {
		boolean_t cancelled;

		/* cancel and free any pending timeout */
		cancelled = thread_call_cancel(shared_region->sr_timer_call);
		if (cancelled) {
			thread_call_free(shared_region->sr_timer_call);
			shared_region->sr_timer_call = NULL;
			/* release the reference held by the cancelled timer */
			shared_region->sr_ref_count--;
		} else {
			/* the timer will drop the reference and free itself */
		}
	}

	SHARED_REGION_TRACE_DEBUG(
		("shared_region: reference_locked(%p) <- %d\n",
		 (void *)VM_KERNEL_ADDRPERM(shared_region),
		 shared_region->sr_ref_count));
}