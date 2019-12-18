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
struct page {int dummy; } ;
struct mm_struct {int dummy; } ;
struct mem_cgroup {int /*<<< orphan*/  css; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  PageSwapCache (struct page*) ; 
 int __mem_cgroup_try_charge (struct mm_struct*,int /*<<< orphan*/ ,struct mem_cgroup**,int,struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  css_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_swap_account ; 
 struct mm_struct init_mm ; 
 scalar_t__ mem_cgroup_disabled () ; 
 struct mem_cgroup* try_get_mem_cgroup_from_page (struct page*) ; 
 scalar_t__ unlikely (int) ; 

int mem_cgroup_try_charge_swapin(struct mm_struct *mm,
				 struct page *page,
				 gfp_t mask, struct mem_cgroup **ptr)
{
	struct mem_cgroup *mem;
	int ret;

	if (mem_cgroup_disabled())
		return 0;

	if (!do_swap_account)
		goto charge_cur_mm;
	/*
	 * A racing thread's fault, or swapoff, may have already updated
	 * the pte, and even removed page from swap cache: in those cases
	 * do_swap_page()'s pte_same() test will fail; but there's also a
	 * KSM case which does need to charge the page.
	 */
	if (!PageSwapCache(page))
		goto charge_cur_mm;
	mem = try_get_mem_cgroup_from_page(page);
	if (!mem)
		goto charge_cur_mm;
	*ptr = mem;
	ret = __mem_cgroup_try_charge(NULL, mask, ptr, true, page, PAGE_SIZE);
	css_put(&mem->css);
	return ret;
charge_cur_mm:
	if (unlikely(!mm))
		mm = &init_mm;
	return __mem_cgroup_try_charge(mm, mask, ptr, true, page, PAGE_SIZE);
}