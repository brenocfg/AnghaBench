#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct page {int dummy; } ;
struct memtype {int type; } ;
struct TYPE_2__ {scalar_t__ (* is_untracked_pat_range ) (int,scalar_t__) ;} ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 scalar_t__ PAGE_SIZE ; 
 int _PAGE_CACHE_UC_MINUS ; 
 int _PAGE_CACHE_WB ; 
 int get_page_memtype (struct page*) ; 
 int /*<<< orphan*/  memtype_lock ; 
 struct memtype* memtype_rb_search (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memtype_rbroot ; 
 scalar_t__ pat_pagerange_is_ram (int,scalar_t__) ; 
 struct page* pfn_to_page (int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (int,scalar_t__) ; 
 TYPE_1__ x86_platform ; 

__attribute__((used)) static unsigned long lookup_memtype(u64 paddr)
{
	int rettype = _PAGE_CACHE_WB;
	struct memtype *entry;

	if (x86_platform.is_untracked_pat_range(paddr, paddr + PAGE_SIZE))
		return rettype;

	if (pat_pagerange_is_ram(paddr, paddr + PAGE_SIZE)) {
		struct page *page;
		page = pfn_to_page(paddr >> PAGE_SHIFT);
		rettype = get_page_memtype(page);
		/*
		 * -1 from get_page_memtype() implies RAM page is in its
		 * default state and not reserved, and hence of type WB
		 */
		if (rettype == -1)
			rettype = _PAGE_CACHE_WB;

		return rettype;
	}

	spin_lock(&memtype_lock);

	entry = memtype_rb_search(&memtype_rbroot, paddr);
	if (entry != NULL)
		rettype = entry->type;
	else
		rettype = _PAGE_CACHE_UC_MINUS;

	spin_unlock(&memtype_lock);
	return rettype;
}