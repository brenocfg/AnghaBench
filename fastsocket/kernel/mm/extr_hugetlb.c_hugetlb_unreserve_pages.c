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
struct inode {long i_blocks; int /*<<< orphan*/  i_lock; TYPE_1__* i_mapping; } ;
struct hugepage_subpool {int dummy; } ;
struct hstate {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  private_list; } ;

/* Variables and functions */
 long blocks_per_huge_page (struct hstate*) ; 
 struct hstate* hstate_inode (struct inode*) ; 
 int /*<<< orphan*/  hugepage_subpool_put_pages (struct hugepage_subpool*,long) ; 
 int /*<<< orphan*/  hugetlb_acct_memory (struct hstate*,long) ; 
 long region_truncate (int /*<<< orphan*/ *,long) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct hugepage_subpool* subpool_inode (struct inode*) ; 

void hugetlb_unreserve_pages(struct inode *inode, long offset, long freed)
{
	struct hstate *h = hstate_inode(inode);
	long chg = region_truncate(&inode->i_mapping->private_list, offset);
	struct hugepage_subpool *spool = subpool_inode(inode);

	spin_lock(&inode->i_lock);
	inode->i_blocks -= (blocks_per_huge_page(h) * freed);
	spin_unlock(&inode->i_lock);

	hugepage_subpool_put_pages(spool, (chg - freed));
	hugetlb_acct_memory(h, -(chg - freed));
}