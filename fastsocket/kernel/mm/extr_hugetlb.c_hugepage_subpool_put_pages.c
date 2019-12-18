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
struct hugepage_subpool {long used_hpages; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlock_or_release_subpool (struct hugepage_subpool*) ; 

__attribute__((used)) static void hugepage_subpool_put_pages(struct hugepage_subpool *spool,
				       long delta)
{
	if (!spool)
		return;

	spin_lock(&spool->lock);
	spool->used_hpages -= delta;
	/* If hugetlbfs_put_super couldn't free spool due to
	* an outstanding quota reference, free it now. */
	unlock_or_release_subpool(spool);
}