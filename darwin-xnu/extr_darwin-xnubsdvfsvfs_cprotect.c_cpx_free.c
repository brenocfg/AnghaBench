#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* cpx_t ;
struct TYPE_4__ {int /*<<< orphan*/  cpx_max_key_len; int /*<<< orphan*/  cpx_cached_key; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void cpx_free(cpx_t cpx)
{

#if DEBUG
	assert(cpx->cpx_magic1 == cpx_magic1);
	assert(*PTR_ADD(uint32_t *, cpx, cpx_sizex(cpx) - 4) == cpx_magic2);
#endif
	
#if CONFIG_KEYPAGE_WP
	/* unprotect the page before bzeroing */
	void *cpxstart = (void*)cpx;
	void *cpxend = (void*)((uint8_t*)cpx + PAGE_SIZE); 
	if (cpx->cpx_flags & CPX_WRITE_PROTECTABLE) {
		vm_map_protect (kernel_map, (vm_map_offset_t)cpxstart, (vm_map_offset_t)cpxend, (VM_PROT_DEFAULT), FALSE);

		//now zero the memory after un-protecting it
		bzero(cpx->cpx_cached_key, cpx->cpx_max_key_len);

		//If we are here, then we used kmem_alloc to get the page. Must use kmem_free to drop it.
		kmem_free(kernel_map, (vm_offset_t)cpx, PAGE_SIZE);
		return;
	}
#else 
	bzero(cpx->cpx_cached_key, cpx->cpx_max_key_len);
	FREE(cpx, M_TEMP);
	return;
#endif

}