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
struct gen_pool {int dummy; } ;
struct TYPE_2__ {struct gen_pool* pool; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 unsigned long __IA64_UNCACHED_OFFSET ; 
 int /*<<< orphan*/  gen_pool_free (struct gen_pool*,unsigned long,int) ; 
 int paddr_to_nid (unsigned long) ; 
 int /*<<< orphan*/  panic (char*,unsigned long) ; 
 TYPE_1__* uncached_pools ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

void uncached_free_page(unsigned long uc_addr, int n_pages)
{
	int nid = paddr_to_nid(uc_addr - __IA64_UNCACHED_OFFSET);
	struct gen_pool *pool = uncached_pools[nid].pool;

	if (unlikely(pool == NULL))
		return;

	if ((uc_addr & (0XFUL << 60)) != __IA64_UNCACHED_OFFSET)
		panic("uncached_free_page invalid address %lx\n", uc_addr);

	gen_pool_free(pool, uc_addr, n_pages * PAGE_SIZE);
}