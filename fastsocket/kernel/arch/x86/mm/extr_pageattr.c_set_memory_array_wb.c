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
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  _PAGE_CACHE_MASK ; 
 scalar_t__ __pa (unsigned long) ; 
 int /*<<< orphan*/  __pgprot (int /*<<< orphan*/ ) ; 
 int change_page_attr_clear (unsigned long*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free_memtype (scalar_t__,scalar_t__) ; 

int set_memory_array_wb(unsigned long *addr, int addrinarray)
{
	int i;
	int ret;

	ret = change_page_attr_clear(addr, addrinarray,
				      __pgprot(_PAGE_CACHE_MASK), 1);
	if (ret)
		return ret;

	for (i = 0; i < addrinarray; i++)
		free_memtype(__pa(addr[i]), __pa(addr[i]) + PAGE_SIZE);

	return 0;
}