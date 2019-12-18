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
struct vm_struct {unsigned long size; unsigned long nr_pages; scalar_t__ phys_addr; int /*<<< orphan*/ * pages; void* addr; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  VM_IOREMAP ; 
 unsigned long __get_free_pages (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free_pages (unsigned long,int) ; 
 int get_order (unsigned long) ; 
 struct vm_struct* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scrub_pages (unsigned long,unsigned long) ; 

struct vm_struct *xen_alloc_vm_area(unsigned long size)
{
	int order;
	unsigned long virt;
	unsigned long nr_pages;
	struct vm_struct *area;

	order = get_order(size);
	virt = __get_free_pages(GFP_KERNEL, order);
	if (virt == 0)
		goto err0;
	nr_pages = 1 << order;
	scrub_pages(virt, nr_pages);

	area = kmalloc(sizeof(*area), GFP_KERNEL);
	if (area == NULL)
		goto err1;

	area->flags = VM_IOREMAP;
	area->addr = (void *)virt;
	area->size = size;
	area->pages = NULL;
	area->nr_pages = nr_pages;
	area->phys_addr = 0;	/* xenbus_map_ring_valloc uses this field!  */

	return area;

err1:
	free_pages(virt, order);
err0:
	return NULL;
}