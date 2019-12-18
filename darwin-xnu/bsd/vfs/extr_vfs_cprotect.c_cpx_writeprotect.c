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
typedef  int /*<<< orphan*/  vm_map_offset_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  TYPE_1__* cpx_t ;
struct TYPE_3__ {int cpx_flags; } ;

/* Variables and functions */
 int CPX_WRITE_PROTECTABLE ; 
 int /*<<< orphan*/  FALSE ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  VM_PROT_READ ; 
 int /*<<< orphan*/  kernel_map ; 
 int /*<<< orphan*/  vm_map_protect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

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