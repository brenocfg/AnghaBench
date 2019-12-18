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
struct vm_struct {unsigned long size; scalar_t__ addr; } ;
struct page {int dummy; } ;
typedef  int /*<<< orphan*/  pgprot_t ;

/* Variables and functions */
 unsigned long PAGE_SIZE ; 
 int vmap_page_range (unsigned long,unsigned long,int /*<<< orphan*/ ,struct page**) ; 

int map_vm_area(struct vm_struct *area, pgprot_t prot, struct page ***pages)
{
	unsigned long addr = (unsigned long)area->addr;
	unsigned long end = addr + area->size - PAGE_SIZE;
	int err;

	err = vmap_page_range(addr, end, prot, *pages);
	if (err > 0) {
		*pages += err;
		err = 0;
	}

	return err;
}