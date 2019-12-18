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
 int /*<<< orphan*/  CPA_ARRAY ; 
 scalar_t__ PAGE_SIZE ; 
 unsigned long _PAGE_CACHE_MASK ; 
 unsigned long _PAGE_CACHE_UC_MINUS ; 
 unsigned long _PAGE_CACHE_WC ; 
 scalar_t__ __pa (unsigned long) ; 
 int /*<<< orphan*/  __pgprot (unsigned long) ; 
 int change_page_attr_set (unsigned long*,int,int /*<<< orphan*/ ,int) ; 
 int change_page_attr_set_clr (unsigned long*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_memtype (scalar_t__,scalar_t__) ; 
 int reserve_memtype (scalar_t__,scalar_t__,unsigned long,int /*<<< orphan*/ *) ; 

int _set_memory_array(unsigned long *addr, int addrinarray,
		unsigned long new_type)
{
	int i, j;
	int ret;

	/*
	 * for now UC MINUS. see comments in ioremap_nocache()
	 */
	for (i = 0; i < addrinarray; i++) {
		ret = reserve_memtype(__pa(addr[i]), __pa(addr[i]) + PAGE_SIZE,
					new_type, NULL);
		if (ret)
			goto out_free;
	}

	ret = change_page_attr_set(addr, addrinarray,
				    __pgprot(_PAGE_CACHE_UC_MINUS), 1);

	if (!ret && new_type == _PAGE_CACHE_WC)
		ret = change_page_attr_set_clr(addr, addrinarray,
					       __pgprot(_PAGE_CACHE_WC),
					       __pgprot(_PAGE_CACHE_MASK),
					       0, CPA_ARRAY, NULL);
	if (ret)
		goto out_free;

	return 0;

out_free:
	for (j = 0; j < i; j++)
		free_memtype(__pa(addr[j]), __pa(addr[j]) + PAGE_SIZE);

	return ret;
}