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
typedef  scalar_t__ vm_address_t ;
typedef  scalar_t__ vaddr ;

/* Variables and functions */
 scalar_t__ gPhysBase ; 
 scalar_t__ gPhysSize ; 
 scalar_t__ gVirtBase ; 
 int /*<<< orphan*/  panic (char*,void*) ; 

vm_offset_t
ml_static_vtop(
		  vm_offset_t vaddr)
{
	if (((vm_address_t)(vaddr) - gVirtBase) >= gPhysSize) 
		panic("ml_static_ptovirt(): illegal vaddr: %p\n", (void*)vaddr);
	return ((vm_address_t)(vaddr) - gVirtBase + gPhysBase);
}