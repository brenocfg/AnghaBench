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
typedef  scalar_t__ vm_offset_t ;
typedef  void* caddr_t ;
struct TYPE_2__ {scalar_t__ debug; scalar_t__ active; } ;

/* Variables and functions */
 TYPE_1__* PROFILE_VARS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kernel_map ; 
 scalar_t__ kmem_alloc (int /*<<< orphan*/ ,scalar_t__*,size_t) ; 
 int /*<<< orphan*/  memset (void*,char,size_t) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 

void *
_profile_alloc_pages (size_t size)
{
	vm_offset_t addr;

	/*
	 * For the MK, we can't support allocating pages at runtime, because we
	 * might be at interrupt level, so abort if we didn't size the table
	 * properly.
	 */

	if (PROFILE_VARS(0)->active) {
		panic("Call to _profile_alloc_pages while profiling is running.");
	}

	if (kmem_alloc(kernel_map, &addr, size)) {
		panic("Could not allocate memory for profiling");
	}

	memset((void *)addr, '\0', size);
	if (PROFILE_VARS(0)->debug) {
		printf("Allocated %d bytes for profiling, address 0x%x\n", (int)size, (int)addr);
	}

	return((caddr_t)addr);
}