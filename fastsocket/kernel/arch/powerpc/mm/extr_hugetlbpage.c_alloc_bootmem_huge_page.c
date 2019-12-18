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
struct huge_bootmem_page {struct hstate* hstate; int /*<<< orphan*/  list; } ;
struct hstate {int dummy; } ;

/* Variables and functions */
 scalar_t__* gpage_freearray ; 
 int /*<<< orphan*/  huge_boot_pages ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t nr_gpages ; 
 struct huge_bootmem_page* phys_to_virt (scalar_t__) ; 

int alloc_bootmem_huge_page(struct hstate *hstate)
{
	struct huge_bootmem_page *m;
	if (nr_gpages == 0)
		return 0;
	m = phys_to_virt(gpage_freearray[--nr_gpages]);
	gpage_freearray[nr_gpages] = 0;
	list_add(&m->list, &huge_boot_pages);
	m->hstate = hstate;
	return 1;
}