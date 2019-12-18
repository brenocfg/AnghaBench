#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_page_t ;
typedef  TYPE_2__* vm_object_t ;
typedef  int vm_object_offset_t ;
typedef  int vm_behavior_t ;
typedef  int uint64_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_10__ {int sequential; } ;
struct TYPE_9__ {scalar_t__ vmp_q_state; int /*<<< orphan*/  vmp_absent; int /*<<< orphan*/  vmp_fictitious; int /*<<< orphan*/  vmp_no_cache; int /*<<< orphan*/  vmp_busy; int /*<<< orphan*/  vmp_laundry; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int PAGE_SIZE ; 
 int PAGE_SIZE_64 ; 
 int /*<<< orphan*/  PMAP_OPTIONS_NOFLUSH ; 
 scalar_t__ TRUE ; 
#define  VM_BEHAVIOR_DEFAULT 131 
#define  VM_BEHAVIOR_RANDOM 130 
#define  VM_BEHAVIOR_RSEQNTL 129 
#define  VM_BEHAVIOR_SEQUENTIAL 128 
 int VM_DEFAULT_DEACTIVATE_BEHIND_CLUSTER ; 
 int /*<<< orphan*/  VM_MEM_REFERENCED ; 
 int /*<<< orphan*/  VM_PAGE_GET_PHYS_PAGE (TYPE_1__*) ; 
 scalar_t__ VM_PAGE_ON_THROTTLED_Q ; 
 int /*<<< orphan*/  dbgTrace (int,unsigned int,unsigned int) ; 
 TYPE_2__* kernel_object ; 
 int /*<<< orphan*/  pmap_clear_refmod_options (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int vm_default_behind ; 
 scalar_t__ vm_page_deactivate_behind ; 
 int /*<<< orphan*/  vm_page_deactivate_behind_count ; 
 int /*<<< orphan*/  vm_page_deactivate_internal (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  vm_page_lockspin_queues () ; 
 TYPE_1__* vm_page_lookup (TYPE_2__*,int) ; 
 int /*<<< orphan*/  vm_page_unlock_queues () ; 

__attribute__((used)) static
boolean_t
vm_fault_deactivate_behind(
	vm_object_t		object,
	vm_object_offset_t	offset,
	vm_behavior_t		behavior)
{
	int		n;
	int		pages_in_run = 0;
	int		max_pages_in_run = 0;
	int		sequential_run;
	int		sequential_behavior = VM_BEHAVIOR_SEQUENTIAL;
	vm_object_offset_t	run_offset = 0;
	vm_object_offset_t	pg_offset = 0;
	vm_page_t	m;
	vm_page_t	page_run[VM_DEFAULT_DEACTIVATE_BEHIND_CLUSTER];

	pages_in_run = 0;
#if TRACEFAULTPAGE
	dbgTrace(0xBEEF0018, (unsigned int) object, (unsigned int) vm_fault_deactivate_behind);	/* (TEST/DEBUG) */
#endif

	if (object == kernel_object || vm_page_deactivate_behind == FALSE) {
		/*
		 * Do not deactivate pages from the kernel object: they
		 * are not intended to become pageable.
		 * or we've disabled the deactivate behind mechanism
		 */
		return FALSE;
	}
	if ((sequential_run = object->sequential)) {
		  if (sequential_run < 0) {
		          sequential_behavior = VM_BEHAVIOR_RSEQNTL;
			  sequential_run = 0 - sequential_run;
		  } else {
		          sequential_behavior = VM_BEHAVIOR_SEQUENTIAL;
		  }
	}
	switch (behavior) {
	case VM_BEHAVIOR_RANDOM:
		break;
	case VM_BEHAVIOR_SEQUENTIAL:
	        if (sequential_run >= (int)PAGE_SIZE) {
			run_offset = 0 - PAGE_SIZE_64;
			max_pages_in_run = 1;
		}
		break;
	case VM_BEHAVIOR_RSEQNTL:
	        if (sequential_run >= (int)PAGE_SIZE) {
			run_offset = PAGE_SIZE_64;
			max_pages_in_run = 1;
		}
		break;
	case VM_BEHAVIOR_DEFAULT:
	default:
	{	vm_object_offset_t behind = vm_default_behind * PAGE_SIZE_64;

	        /*
		 * determine if the run of sequential accesss has been
		 * long enough on an object with default access behavior
		 * to consider it for deactivation
		 */
		if ((uint64_t)sequential_run >= behind && (sequential_run % (VM_DEFAULT_DEACTIVATE_BEHIND_CLUSTER * PAGE_SIZE)) == 0) {
			/*
			 * the comparisons between offset and behind are done
			 * in this kind of odd fashion in order to prevent wrap around
			 * at the end points
			 */
		        if (sequential_behavior == VM_BEHAVIOR_SEQUENTIAL) {
			        if (offset >= behind) {
					run_offset = 0 - behind;
					pg_offset = PAGE_SIZE_64;
					max_pages_in_run = VM_DEFAULT_DEACTIVATE_BEHIND_CLUSTER;
				}
			} else {
			        if (offset < -behind) {
					run_offset = behind;
					pg_offset = 0 - PAGE_SIZE_64;
					max_pages_in_run = VM_DEFAULT_DEACTIVATE_BEHIND_CLUSTER;
				}
			}
		}
		break;
	}
	}
        for (n = 0; n < max_pages_in_run; n++) {
		m = vm_page_lookup(object, offset + run_offset + (n * pg_offset));

		if (m && !m->vmp_laundry && !m->vmp_busy && !m->vmp_no_cache && (m->vmp_q_state != VM_PAGE_ON_THROTTLED_Q) && !m->vmp_fictitious && !m->vmp_absent) {
			page_run[pages_in_run++] = m;

			/*
			 * by not passing in a pmap_flush_context we will forgo any TLB flushing, local or otherwise...
			 *
			 * a TLB flush isn't really needed here since at worst we'll miss the reference bit being
			 * updated in the PTE if a remote processor still has this mapping cached in its TLB when the
			 * new reference happens. If no futher references happen on the page after that remote TLB flushes
			 * we'll see a clean, non-referenced page when it eventually gets pulled out of the inactive queue
			 * by pageout_scan, which is just fine since the last reference would have happened quite far
			 * in the past (TLB caches don't hang around for very long), and of course could just as easily
			 * have happened before we did the deactivate_behind.
			 */
			pmap_clear_refmod_options(VM_PAGE_GET_PHYS_PAGE(m), VM_MEM_REFERENCED, PMAP_OPTIONS_NOFLUSH, (void *)NULL);
		}
	}
	if (pages_in_run) {
		vm_page_lockspin_queues();

		for (n = 0; n < pages_in_run; n++) {

			m = page_run[n];

			vm_page_deactivate_internal(m, FALSE);

			vm_page_deactivate_behind_count++;
#if TRACEFAULTPAGE
			dbgTrace(0xBEEF0019, (unsigned int) object, (unsigned int) m);	/* (TEST/DEBUG) */
#endif
		}
		vm_page_unlock_queues();

		return TRUE;
	}
	return FALSE;
}