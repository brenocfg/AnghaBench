#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ vm_offset_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 scalar_t__ ARM_PGBYTES ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  avail_start ; 
 scalar_t__ phystokv (int /*<<< orphan*/ ) ; 
 scalar_t__ ropage_next ; 
 int /*<<< orphan*/  ropagetable_begin ; 
 int /*<<< orphan*/  ropagetable_end ; 

vm_offset_t alloc_ptpage(boolean_t map_static) {
	vm_offset_t vaddr;

#if !(defined(KERNEL_INTEGRITY_KTRR))
	map_static = FALSE;
#endif

	if (!ropage_next) {
		ropage_next = (vm_offset_t)&ropagetable_begin;
	}

	if (map_static) {
		assert(ropage_next < (vm_offset_t)&ropagetable_end);

		vaddr = ropage_next;
		ropage_next += ARM_PGBYTES;

		return vaddr;
	} else {
		vaddr = phystokv(avail_start);
		avail_start += ARM_PGBYTES;

		return vaddr;
	}
}