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
typedef  scalar_t__ vm_address_t ;
typedef  scalar_t__ va ;
struct TYPE_2__ {scalar_t__ len; scalar_t__ va; scalar_t__ pa; } ;

/* Variables and functions */
 size_t PTOV_TABLE_SIZE ; 
 scalar_t__ gPhysBase ; 
 scalar_t__ gPhysSize ; 
 scalar_t__ gVirtBase ; 
 int /*<<< orphan*/  panic (char*,void*) ; 
 TYPE_1__* ptov_table ; 

vm_offset_t
ml_static_vtop(vm_offset_t va)
{
	for (size_t i = 0; (i < PTOV_TABLE_SIZE) && (ptov_table[i].len != 0); i++) {
		if ((va >= ptov_table[i].va) && (va < (ptov_table[i].va + ptov_table[i].len)))
			return (va - ptov_table[i].va + ptov_table[i].pa);
	}
	if (((vm_address_t)(va) - gVirtBase) >= gPhysSize)
		panic("ml_static_vtop(): illegal VA: %p\n", (void*)va);
	return ((vm_address_t)(va) - gVirtBase + gPhysBase);
}