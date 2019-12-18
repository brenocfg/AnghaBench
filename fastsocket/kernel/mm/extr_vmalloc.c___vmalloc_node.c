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
struct vm_struct {int dummy; } ;
typedef  int /*<<< orphan*/  pgprot_t ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 unsigned long PAGE_ALIGN (unsigned long) ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  VMALLOC_END ; 
 int /*<<< orphan*/  VMALLOC_START ; 
 int VM_ALLOC ; 
 int VM_UNLIST ; 
 struct vm_struct* __get_vm_area_node (unsigned long,unsigned long,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,void*) ; 
 void* __vmalloc_area_node (struct vm_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,void*) ; 
 int /*<<< orphan*/  insert_vmalloc_vmlist (struct vm_struct*) ; 
 int /*<<< orphan*/  kmemleak_alloc (void*,unsigned long,int,int /*<<< orphan*/ ) ; 
 unsigned long totalram_pages ; 

__attribute__((used)) static void *__vmalloc_node(unsigned long size, unsigned long align,
			    gfp_t gfp_mask, pgprot_t prot,
			    int node, void *caller)
{
	struct vm_struct *area;
	void *addr;
	unsigned long real_size = size;

	size = PAGE_ALIGN(size);
	if (!size || (size >> PAGE_SHIFT) > totalram_pages)
		return NULL;

	area = __get_vm_area_node(size, align, VM_ALLOC | VM_UNLIST, VMALLOC_START,
				  VMALLOC_END, node, gfp_mask, caller);

	if (!area)
		return NULL;

	addr = __vmalloc_area_node(area, gfp_mask, prot, node, caller);
	if (!addr)
		return NULL;

 	/*
	 * In this function, newly allocated vm_struct is not added
	 * to vmlist at __get_vm_area_node(). so, it is added here.
	 */
	insert_vmalloc_vmlist(area);

	/*
	 * A ref_count = 3 is needed because the vm_struct and vmap_area
	 * structures allocated in the __get_vm_area_node() function contain
	 * references to the virtual address of the vmalloc'ed block.
	 */
	kmemleak_alloc(addr, real_size, 3, gfp_mask);

	return addr;
}