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
struct vm_struct {int phys_addr; scalar_t__ addr; } ;
struct sq_mapping {int addr; scalar_t__ size; int /*<<< orphan*/  sq_addr; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  SQ_ADDRMAX ; 
 int /*<<< orphan*/  SQ_QACR0 ; 
 int /*<<< orphan*/  SQ_QACR1 ; 
 int /*<<< orphan*/  VM_ALLOC ; 
 struct vm_struct* __get_vm_area (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __pgprot (unsigned long) ; 
 int /*<<< orphan*/  ctrl_outl (int,int /*<<< orphan*/ ) ; 
 scalar_t__ ioremap_page_range (unsigned long,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vunmap (scalar_t__) ; 

__attribute__((used)) static int __sq_remap(struct sq_mapping *map, unsigned long flags)
{
#if defined(CONFIG_MMU)
	struct vm_struct *vma;

	vma = __get_vm_area(map->size, VM_ALLOC, map->sq_addr, SQ_ADDRMAX);
	if (!vma)
		return -ENOMEM;

	vma->phys_addr = map->addr;

	if (ioremap_page_range((unsigned long)vma->addr,
			       (unsigned long)vma->addr + map->size,
			       vma->phys_addr, __pgprot(flags))) {
		vunmap(vma->addr);
		return -EAGAIN;
	}
#else
	/*
	 * Without an MMU (or with it turned off), this is much more
	 * straightforward, as we can just load up each queue's QACR with
	 * the physical address appropriately masked.
	 */
	ctrl_outl(((map->addr >> 26) << 2) & 0x1c, SQ_QACR0);
	ctrl_outl(((map->addr >> 26) << 2) & 0x1c, SQ_QACR1);
#endif

	return 0;
}