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
typedef  size_t uint32_t ;
struct mtrace {int allocs; scalar_t__ depth; scalar_t__ collisions; int /*<<< orphan*/  addr; int /*<<< orphan*/  hitcount; } ;
struct mallocation {size_t trace_index; int count; int /*<<< orphan*/ * element; int /*<<< orphan*/  hitcount; } ;
typedef  int /*<<< orphan*/  mcache_obj_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_2__ {int /*<<< orphan*/  outstanding_allocs; int /*<<< orphan*/  alloc_recorded; int /*<<< orphan*/  alloc_overwrites; int /*<<< orphan*/  alloc_collisions; int /*<<< orphan*/  trace_recorded; int /*<<< orphan*/  trace_overwrites; int /*<<< orphan*/  trace_collisions; int /*<<< orphan*/  total_conflicts; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 scalar_t__ bcmp (int /*<<< orphan*/ ,uintptr_t*,size_t) ; 
 size_t hashaddr (uintptr_t,int) ; 
 size_t hashbacktrace (uintptr_t*,size_t,int) ; 
 int /*<<< orphan*/  lck_mtx_try_lock_spin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,uintptr_t*,size_t) ; 
 int mleak_alloc_buckets ; 
 struct mallocation* mleak_allocations ; 
 int /*<<< orphan*/  mleak_lock ; 
 TYPE_1__ mleak_table ; 
 int mleak_trace_buckets ; 
 struct mtrace* mleak_traces ; 

__attribute__((used)) static boolean_t
mleak_log(uintptr_t *bt, mcache_obj_t *addr, uint32_t depth, int num)
{
	struct mallocation *allocation;
	struct mtrace *trace;
	uint32_t trace_index;

	/* Quit if someone else modifying the tables */
	if (!lck_mtx_try_lock_spin(mleak_lock)) {
		mleak_table.total_conflicts++;
		return (FALSE);
	}

	allocation = &mleak_allocations[hashaddr((uintptr_t)addr,
	    mleak_alloc_buckets)];
	trace_index = hashbacktrace(bt, depth, mleak_trace_buckets);
	trace = &mleak_traces[trace_index];

	VERIFY(allocation <= &mleak_allocations[mleak_alloc_buckets - 1]);
	VERIFY(trace <= &mleak_traces[mleak_trace_buckets - 1]);

	allocation->hitcount++;
	trace->hitcount++;

	/*
	 * If the allocation bucket we want is occupied
	 * and the occupier has the same trace, just bail.
	 */
	if (allocation->element != NULL &&
	    trace_index == allocation->trace_index) {
		mleak_table.alloc_collisions++;
		lck_mtx_unlock(mleak_lock);
		return (TRUE);
	}

	/*
	 * Store the backtrace in the traces array;
	 * Size of zero = trace bucket is free.
	 */
	if (trace->allocs > 0 &&
	    bcmp(trace->addr, bt, (depth * sizeof (uintptr_t))) != 0) {
		/* Different, unique trace, but the same hash! Bail out. */
		trace->collisions++;
		mleak_table.trace_collisions++;
		lck_mtx_unlock(mleak_lock);
		return (TRUE);
	} else if (trace->allocs > 0) {
		/* Same trace, already added, so increment refcount */
		trace->allocs++;
	} else {
		/* Found an unused trace bucket, so record the trace here */
		if (trace->depth != 0) {
			/* this slot previously used but not currently in use */
			mleak_table.trace_overwrites++;
		}
		mleak_table.trace_recorded++;
		trace->allocs = 1;
		memcpy(trace->addr, bt, (depth * sizeof (uintptr_t)));
		trace->depth = depth;
		trace->collisions = 0;
	}

	/* Step 2: Store the allocation record in the allocations array */
	if (allocation->element != NULL) {
		/*
		 * Replace an existing allocation.  No need to preserve
		 * because only a subset of the allocations are being
		 * recorded anyway.
		 */
		mleak_table.alloc_collisions++;
	} else if (allocation->trace_index != 0) {
		mleak_table.alloc_overwrites++;
	}
	allocation->element = addr;
	allocation->trace_index = trace_index;
	allocation->count = num;
	mleak_table.alloc_recorded++;
	mleak_table.outstanding_allocs++;

	lck_mtx_unlock(mleak_lock);
	return (TRUE);
}