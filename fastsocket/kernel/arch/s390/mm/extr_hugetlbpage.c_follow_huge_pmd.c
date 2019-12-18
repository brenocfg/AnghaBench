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
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 unsigned long HPAGE_MASK ; 
 int /*<<< orphan*/  MACHINE_HAS_HPAGE ; 
 unsigned long PAGE_SHIFT ; 
 struct page* pmd_page (int /*<<< orphan*/ ) ; 

struct page *follow_huge_pmd(struct mm_struct *mm, unsigned long address,
			     pmd_t *pmdp, int write)
{
	struct page *page;

	if (!MACHINE_HAS_HPAGE)
		return NULL;

	page = pmd_page(*pmdp);
	if (page)
		page += ((address & ~HPAGE_MASK) >> PAGE_SHIFT);
	return page;
}