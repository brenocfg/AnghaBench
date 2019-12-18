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
struct hstate {int dummy; } ;
typedef  int /*<<< orphan*/  pud_t ;
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 scalar_t__ PMD_SHIFT ; 
 scalar_t__ huge_page_shift (struct hstate*) ; 
 int /*<<< orphan*/ * pmd_alloc (struct mm_struct*,int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static pmd_t *hpmd_alloc(struct mm_struct *mm, pud_t *pud, unsigned long addr,
			 struct hstate *hstate)
{
	if (huge_page_shift(hstate) < PMD_SHIFT)
		return pmd_alloc(mm, pud, addr);
	else
		return (pmd_t *) pud;
}