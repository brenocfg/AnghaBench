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
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int uint32_t ;
struct TYPE_4__ {int OSMT_attr; } ;
typedef  TYPE_1__* OSMallocTag ;

/* Variables and functions */
 int OSMT_PAGEABLE ; 
 int /*<<< orphan*/  OSMalloc_Tagrele (TYPE_1__*) ; 
 int PAGE_MASK ; 
 int /*<<< orphan*/  kernel_map ; 
 int /*<<< orphan*/  kfree (void*,int) ; 
 int /*<<< orphan*/  kmem_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
OSFree(
	void				*addr,
	uint32_t			size,
	OSMallocTag			tag) 
{
	if ((tag->OSMT_attr & OSMT_PAGEABLE)
	    && (size & ~PAGE_MASK)) {
		kmem_free(kernel_map, (vm_offset_t)addr, size);
	} else
		kfree((void *)addr, size);

	OSMalloc_Tagrele(tag);
}