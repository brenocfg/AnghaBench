#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_size_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_5__ {int OSMT_attr; } ;
typedef  TYPE_1__* OSMallocTag ;

/* Variables and functions */
 int OSMT_PAGEABLE ; 
 int /*<<< orphan*/  OSMalloc_Tagref (TYPE_1__*) ; 
 int /*<<< orphan*/  OSMalloc_Tagrele (TYPE_1__*) ; 
 int /*<<< orphan*/  VM_KERN_MEMORY_KALLOC ; 
 void* kalloc_noblock_tag_bt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void *
OSMalloc_noblock(
	uint32_t			size,
	OSMallocTag			tag)
{
	void	*addr=NULL;

	if (tag->OSMT_attr & OSMT_PAGEABLE)
		return(NULL);

	OSMalloc_Tagref(tag);
	addr = kalloc_noblock_tag_bt((vm_size_t)size, VM_KERN_MEMORY_KALLOC);
	if (addr == NULL)
		OSMalloc_Tagrele(tag);

	return(addr);
}