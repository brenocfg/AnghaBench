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
struct mem_type {int dummy; } ;
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  init_mm ; 
 unsigned long pmd_addr_end (unsigned long,unsigned long) ; 
 int /*<<< orphan*/ * pmd_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long) ; 
 int remap_area_pte (int /*<<< orphan*/ *,unsigned long,unsigned long,unsigned long,struct mem_type const*) ; 

__attribute__((used)) static inline int remap_area_pmd(pgd_t *pgd, unsigned long addr,
				 unsigned long end, unsigned long phys_addr,
				 const struct mem_type *type)
{
	unsigned long next;
	pmd_t *pmd;
	int ret = 0;

	pmd = pmd_alloc(&init_mm, pgd, addr);
	if (!pmd)
		return -ENOMEM;

	do {
		next = pmd_addr_end(addr, end);
		ret = remap_area_pte(pmd, addr, next, phys_addr, type);
		if (ret)
			return ret;
		phys_addr += next - addr;
	} while (pmd++, addr = next, addr != end);
	return ret;
}