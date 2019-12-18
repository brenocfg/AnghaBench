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
struct mm_struct {int dummy; } ;
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 int GFP_KERNEL ; 
 scalar_t__ PAGE_SHIFT ; 
 int PGDIR_ORDER ; 
 int __GFP_ZERO ; 
 scalar_t__ __get_free_pages (int,scalar_t__) ; 
 scalar_t__ kzalloc (int,int) ; 

pgd_t *pgd_alloc(struct mm_struct *mm)
{
	pgd_t *ret;

	/* pgdir take page or two with 4K pages and a page fraction otherwise */
#ifndef CONFIG_PPC_4K_PAGES
	ret = (pgd_t *)kzalloc(1 << PGDIR_ORDER, GFP_KERNEL);
#else
	ret = (pgd_t *)__get_free_pages(GFP_KERNEL|__GFP_ZERO,
			PGDIR_ORDER - PAGE_SHIFT);
#endif
	return ret;
}