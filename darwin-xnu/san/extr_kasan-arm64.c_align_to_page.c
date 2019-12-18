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
 int /*<<< orphan*/  ARM_PGMASK ; 
 scalar_t__ vm_map_round_page (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ vm_map_trunc_page (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
align_to_page(vm_offset_t *addrp, vm_offset_t *sizep)
{
	vm_offset_t addr_aligned = vm_map_trunc_page(*addrp, ARM_PGMASK);
	*sizep = vm_map_round_page(*sizep + (*addrp - addr_aligned), ARM_PGMASK);
	*addrp = addr_aligned;
}