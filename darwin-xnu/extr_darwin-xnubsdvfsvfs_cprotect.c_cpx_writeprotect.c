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
typedef  int /*<<< orphan*/  cpx_t ;

/* Variables and functions */

void cpx_writeprotect (cpx_t cpx) 
{
#if CONFIG_KEYPAGE_WP
	void *cpxstart = (void*)cpx;
	void *cpxend = (void*)((uint8_t*)cpx + PAGE_SIZE);
	if (cpx->cpx_flags & CPX_WRITE_PROTECTABLE) {
		vm_map_protect (kernel_map, (vm_map_offset_t)cpxstart, (vm_map_offset_t)cpxend, (VM_PROT_READ), FALSE);
	}
#else
	(void) cpx;
#endif
	return;
}