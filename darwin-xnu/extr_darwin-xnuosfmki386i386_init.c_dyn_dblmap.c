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

/* Variables and functions */
 scalar_t__ PAGE_MASK ; 
 int /*<<< orphan*/  PMAP_EXPAND_OPTIONS_ALIASMAP ; 
 int VM_PROT_READ ; 
 int VM_PROT_WRITE ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ dblmap_max ; 
 int /*<<< orphan*/  pmap_alias (scalar_t__,scalar_t__,scalar_t__,int,int /*<<< orphan*/ ) ; 

vm_offset_t dyn_dblmap(vm_offset_t cva, vm_offset_t sz) {
	vm_offset_t ava = dblmap_max;

	assert((sz & PAGE_MASK) == 0);
	assert(cva != 0);

	pmap_alias(ava, cva, cva + sz, VM_PROT_READ | VM_PROT_WRITE, PMAP_EXPAND_OPTIONS_ALIASMAP);
	dblmap_max += sz;
	return (ava - cva);
}