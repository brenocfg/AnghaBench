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
struct mm_struct {int /*<<< orphan*/  page_table_lock; } ;
typedef  int /*<<< orphan*/  spinlock_t ;

/* Variables and functions */
 int /*<<< orphan*/ * __pte_lockptr (struct page*) ; 
 int /*<<< orphan*/  spin_lock_nest_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static spinlock_t *xen_pte_lock(struct page *page, struct mm_struct *mm)
{
	spinlock_t *ptl = NULL;

#if USE_SPLIT_PTLOCKS
	ptl = __pte_lockptr(page);
	spin_lock_nest_lock(ptl, &mm->page_table_lock);
#endif

	return ptl;
}