#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mtrace {scalar_t__ allocs; scalar_t__ depth; } ;
struct mallocation {size_t trace_index; TYPE_1__* element; } ;
struct TYPE_4__ {struct TYPE_4__* obj_next; } ;
typedef  TYPE_1__ mcache_obj_t ;
struct TYPE_5__ {int /*<<< orphan*/  outstanding_allocs; } ;

/* Variables and functions */
 size_t hashaddr (uintptr_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_lock_spin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mleak_alloc_buckets ; 
 struct mallocation* mleak_allocations ; 
 int /*<<< orphan*/  mleak_lock ; 
 TYPE_2__ mleak_table ; 
 size_t mleak_trace_buckets ; 
 struct mtrace* mleak_traces ; 

__attribute__((used)) static void
mleak_free(mcache_obj_t *addr)
{
	while (addr != NULL) {
		struct mallocation *allocation = &mleak_allocations
		    [hashaddr((uintptr_t)addr, mleak_alloc_buckets)];

		if (allocation->element == addr &&
		    allocation->trace_index < mleak_trace_buckets) {
			lck_mtx_lock_spin(mleak_lock);
			if (allocation->element == addr &&
			    allocation->trace_index < mleak_trace_buckets) {
				struct mtrace *trace;
				trace = &mleak_traces[allocation->trace_index];
				/* allocs = 0 means trace bucket is unused */
				if (trace->allocs > 0)
					trace->allocs--;
				if (trace->allocs == 0)
					trace->depth = 0;
				/* NULL element means alloc bucket is unused */
				allocation->element = NULL;
				mleak_table.outstanding_allocs--;
			}
			lck_mtx_unlock(mleak_lock);
		}
		addr = addr->obj_next;
	}
}