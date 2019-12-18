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
typedef  int /*<<< orphan*/  pud_t ;
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 
 unsigned long PUD_MASK ; 
 struct page* pte_page (int /*<<< orphan*/ ) ; 

struct page *
follow_huge_pud(struct mm_struct *mm, unsigned long address,
		pud_t *pud, int write)
{
	struct page *page;

	page = pte_page(*(pte_t *)pud);
	if (page)
		page += ((address & ~PUD_MASK) >> PAGE_SHIFT);
	return page;
}