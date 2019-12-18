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
typedef  int /*<<< orphan*/  pud_t ;
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 unsigned long PGDIR_SIZE ; 
 unsigned long __START_KERNEL_map ; 
 int /*<<< orphan*/  __pa (unsigned long) ; 
 scalar_t__ get_safe_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * init_level4_pgt ; 
 int /*<<< orphan*/  max_pfn ; 
 int /*<<< orphan*/  mk_kernel_pgd (int /*<<< orphan*/ ) ; 
 scalar_t__ pfn_to_kaddr (int /*<<< orphan*/ ) ; 
 int pgd_index (unsigned long) ; 
 int res_phys_pud_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_pgd (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * temp_level4_pgt ; 

__attribute__((used)) static int set_up_temporary_mappings(void)
{
	unsigned long start, end, next;
	int error;

	temp_level4_pgt = (pgd_t *)get_safe_page(GFP_ATOMIC);
	if (!temp_level4_pgt)
		return -ENOMEM;

	/* It is safe to reuse the original kernel mapping */
	set_pgd(temp_level4_pgt + pgd_index(__START_KERNEL_map),
		init_level4_pgt[pgd_index(__START_KERNEL_map)]);

	/* Set up the direct mapping from scratch */
	start = (unsigned long)pfn_to_kaddr(0);
	end = (unsigned long)pfn_to_kaddr(max_pfn);

	for (; start < end; start = next) {
		pud_t *pud = (pud_t *)get_safe_page(GFP_ATOMIC);
		if (!pud)
			return -ENOMEM;
		next = start + PGDIR_SIZE;
		if (next > end)
			next = end;
		if ((error = res_phys_pud_init(pud, __pa(start), __pa(next))))
			return error;
		set_pgd(temp_level4_pgt + pgd_index(start),
			mk_kernel_pgd(__pa(pud)));
	}
	return 0;
}