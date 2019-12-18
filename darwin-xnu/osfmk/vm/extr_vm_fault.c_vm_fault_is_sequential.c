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
typedef  TYPE_1__* vm_object_t ;
typedef  scalar_t__ vm_object_offset_t ;
typedef  int vm_behavior_t ;
typedef  int /*<<< orphan*/  UInt32 ;
struct TYPE_3__ {int sequential; scalar_t__ last_alloc; } ;

/* Variables and functions */
 int MAX_SEQUENTIAL_RUN ; 
 int /*<<< orphan*/  OSCompareAndSwap (int,int,int /*<<< orphan*/ *) ; 
 int PAGE_SIZE ; 
 scalar_t__ PAGE_SIZE_64 ; 
#define  VM_BEHAVIOR_DEFAULT 131 
#define  VM_BEHAVIOR_RANDOM 130 
#define  VM_BEHAVIOR_RSEQNTL 129 
#define  VM_BEHAVIOR_SEQUENTIAL 128 

__attribute__((used)) static
void
vm_fault_is_sequential(
	vm_object_t		object,
	vm_object_offset_t	offset,
	vm_behavior_t		behavior)
{
        vm_object_offset_t	last_alloc;
	int			sequential;
	int			orig_sequential;

        last_alloc = object->last_alloc;
	sequential = object->sequential;
	orig_sequential = sequential;

	switch (behavior) {
	case VM_BEHAVIOR_RANDOM:
	        /*
		 * reset indicator of sequential behavior
		 */
	        sequential = 0;
	        break;

	case VM_BEHAVIOR_SEQUENTIAL:
	        if (offset && last_alloc == offset - PAGE_SIZE_64) {
		        /*
			 * advance indicator of sequential behavior
			 */
		        if (sequential < MAX_SEQUENTIAL_RUN)
			        sequential += PAGE_SIZE;
		} else {
		        /*
			 * reset indicator of sequential behavior
			 */
		        sequential = 0;
		}
	        break;

	case VM_BEHAVIOR_RSEQNTL:
	        if (last_alloc && last_alloc == offset + PAGE_SIZE_64) {
		        /*
			 * advance indicator of sequential behavior
			 */
		        if (sequential > -MAX_SEQUENTIAL_RUN)
			        sequential -= PAGE_SIZE;
		} else {
		        /*
			 * reset indicator of sequential behavior
			 */
		        sequential = 0;
		}
	        break;

	case VM_BEHAVIOR_DEFAULT:
	default:
	        if (offset && last_alloc == (offset - PAGE_SIZE_64)) {
		        /*
			 * advance indicator of sequential behavior
			 */
		        if (sequential < 0)
			        sequential = 0;
		        if (sequential < MAX_SEQUENTIAL_RUN)
			        sequential += PAGE_SIZE;

		} else if (last_alloc && last_alloc == (offset + PAGE_SIZE_64)) {
		        /*
			 * advance indicator of sequential behavior
			 */
		        if (sequential > 0)
			        sequential = 0;
		        if (sequential > -MAX_SEQUENTIAL_RUN)
			        sequential -= PAGE_SIZE;
		} else {
		        /*
			 * reset indicator of sequential behavior
			 */
		        sequential = 0;
		}
	        break;
	}
	if (sequential != orig_sequential) {
	        if (!OSCompareAndSwap(orig_sequential, sequential, (UInt32 *)&object->sequential)) {
		        /*
			 * if someone else has already updated object->sequential
			 * don't bother trying to update it or object->last_alloc
			 */
		        return;
		}
	}
	/*
	 * I'd like to do this with a OSCompareAndSwap64, but that
	 * doesn't exist for PPC...  however, it shouldn't matter
	 * that much... last_alloc is maintained so that we can determine
	 * if a sequential access pattern is taking place... if only
	 * one thread is banging on this object, no problem with the unprotected
	 * update... if 2 or more threads are banging away, we run the risk of
	 * someone seeing a mangled update... however, in the face of multiple
	 * accesses, no sequential access pattern can develop anyway, so we
	 * haven't lost any real info.
	 */
	object->last_alloc = offset;
}