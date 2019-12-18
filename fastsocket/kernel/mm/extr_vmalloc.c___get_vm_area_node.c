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
struct vmap_area {int dummy; } ;
struct vm_struct {int dummy; } ;
typedef  int gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int GFP_RECLAIM_MASK ; 
 int IOREMAP_MAX_ORDER ; 
 scalar_t__ IS_ERR (struct vmap_area*) ; 
 unsigned long PAGE_ALIGN (unsigned long) ; 
 int PAGE_SHIFT ; 
 scalar_t__ PAGE_SIZE ; 
 unsigned long VM_IOREMAP ; 
 unsigned long VM_UNLIST ; 
 struct vmap_area* alloc_vmap_area (unsigned long,unsigned long,unsigned long,unsigned long,int,int) ; 
 int fls (unsigned long) ; 
 int /*<<< orphan*/  in_interrupt () ; 
 int /*<<< orphan*/  insert_vmalloc_vm (struct vm_struct*,struct vmap_area*,unsigned long,void*) ; 
 int /*<<< orphan*/  kfree (struct vm_struct*) ; 
 struct vm_struct* kzalloc_node (int,int,int) ; 
 int /*<<< orphan*/  setup_vmalloc_vm (struct vm_struct*,struct vmap_area*,unsigned long,void*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct vm_struct *__get_vm_area_node(unsigned long size,
		unsigned long align, unsigned long flags, unsigned long start,
		unsigned long end, int node, gfp_t gfp_mask, void *caller)
{
	static struct vmap_area *va;
	struct vm_struct *area;

	BUG_ON(in_interrupt());
	if (flags & VM_IOREMAP) {
		int bit = fls(size);

		if (bit > IOREMAP_MAX_ORDER)
			bit = IOREMAP_MAX_ORDER;
		else if (bit < PAGE_SHIFT)
			bit = PAGE_SHIFT;

		align = 1ul << bit;
	}

	size = PAGE_ALIGN(size);
	if (unlikely(!size))
		return NULL;

	area = kzalloc_node(sizeof(*area), gfp_mask & GFP_RECLAIM_MASK, node);
	if (unlikely(!area))
		return NULL;

	/*
	 * We always allocate a guard page.
	 */
	size += PAGE_SIZE;

	va = alloc_vmap_area(size, align, start, end, node, gfp_mask);
	if (IS_ERR(va)) {
		kfree(area);
		return NULL;
	}

	/*
	 * When this function is called from __vmalloc_node_range,
	 * we do not add vm_struct to vmlist here to avoid
	 * accessing uninitialized members of vm_struct such as
	 * pages and nr_pages fields. They will be set later.
	 * To distinguish it from others, we use a VM_UNLIST flag.
	 */
	if (flags & VM_UNLIST)
		setup_vmalloc_vm(area, va, flags, caller);
	else
		insert_vmalloc_vm(area, va, flags, caller);

	return area;
}