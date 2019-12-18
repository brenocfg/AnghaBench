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
typedef  int vm_offset_t ;

/* Variables and functions */
 int ARM_PTE_HINT_ENTRIES_SHIFT ; 
 int ARM_PTE_SIZE ; 

__attribute__((used)) static vm_offset_t
round_up_pte_hint_address(vm_offset_t address)
{
	vm_offset_t hint_size = ARM_PTE_SIZE << ARM_PTE_HINT_ENTRIES_SHIFT;
	return ((address + (hint_size - 1)) & ~(hint_size - 1));
}