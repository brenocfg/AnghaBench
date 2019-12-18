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

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 
#define  _PAGE_CACHE_UC 130 
#define  _PAGE_CACHE_WB 129 
#define  _PAGE_CACHE_WC 128 
 int _set_memory_uc (unsigned long,unsigned long) ; 
 int _set_memory_wb (unsigned long,unsigned long) ; 
 int _set_memory_wc (unsigned long,unsigned long) ; 

int ioremap_change_attr(unsigned long vaddr, unsigned long size,
			       unsigned long prot_val)
{
	unsigned long nrpages = size >> PAGE_SHIFT;
	int err;

	switch (prot_val) {
	case _PAGE_CACHE_UC:
	default:
		err = _set_memory_uc(vaddr, nrpages);
		break;
	case _PAGE_CACHE_WC:
		err = _set_memory_wc(vaddr, nrpages);
		break;
	case _PAGE_CACHE_WB:
		err = _set_memory_wb(vaddr, nrpages);
		break;
	}

	return err;
}