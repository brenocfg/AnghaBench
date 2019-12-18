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
struct list_head {int dummy; } ;
struct kcore_list {unsigned long addr; unsigned long size; int /*<<< orphan*/  list; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KCORE_RAM ; 
 unsigned long PAGE_SHIFT ; 
 unsigned long ULONG_MAX ; 
 unsigned long VMALLOC_START ; 
 scalar_t__ __va (unsigned long) ; 
 int /*<<< orphan*/  get_sparsemem_vmemmap_info (struct kcore_list*,struct list_head*) ; 
 int /*<<< orphan*/  kfree (struct kcore_list*) ; 
 struct kcore_list* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
kclist_add_private(unsigned long pfn, unsigned long nr_pages, void *arg)
{
	struct list_head *head = (struct list_head *)arg;
	struct kcore_list *ent;

	ent = kmalloc(sizeof(*ent), GFP_KERNEL);
	if (!ent)
		return -ENOMEM;
	ent->addr = (unsigned long)__va((pfn << PAGE_SHIFT));
	ent->size = nr_pages << PAGE_SHIFT;

	/* Sanity check: Can happen in 32bit arch...maybe */
	if (ent->addr < (unsigned long) __va(0))
		goto free_out;

	/* cut not-mapped area. ....from ppc-32 code. */
	if (ULONG_MAX - ent->addr < ent->size)
		ent->size = ULONG_MAX - ent->addr;

	/* cut when vmalloc() area is higher than direct-map area */
	if (VMALLOC_START > (unsigned long)__va(0)) {
		if (ent->addr > VMALLOC_START)
			goto free_out;
		if (VMALLOC_START - ent->addr < ent->size)
			ent->size = VMALLOC_START - ent->addr;
	}

	ent->type = KCORE_RAM;
	list_add_tail(&ent->list, head);

	if (!get_sparsemem_vmemmap_info(ent, head)) {
		list_del(&ent->list);
		goto free_out;
	}

	return 0;
free_out:
	kfree(ent);
	return 1;
}