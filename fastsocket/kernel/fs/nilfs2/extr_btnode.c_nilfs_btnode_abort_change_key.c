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
struct nilfs_btnode_chkey_ctxt {scalar_t__ oldkey; scalar_t__ newkey; TYPE_1__* bh; struct buffer_head* newbh; } ;
struct buffer_head {int dummy; } ;
struct address_space {int /*<<< orphan*/  tree_lock; int /*<<< orphan*/  page_tree; } ;
typedef  scalar_t__ __u64 ;
struct TYPE_2__ {int /*<<< orphan*/  b_page; } ;

/* Variables and functions */
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  radix_tree_delete (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlock_page (int /*<<< orphan*/ ) ; 

void nilfs_btnode_abort_change_key(struct address_space *btnc,
				   struct nilfs_btnode_chkey_ctxt *ctxt)
{
	struct buffer_head *nbh = ctxt->newbh;
	__u64 oldkey = ctxt->oldkey, newkey = ctxt->newkey;

	if (oldkey == newkey)
		return;

	if (nbh == NULL) {	/* blocksize == pagesize */
		spin_lock_irq(&btnc->tree_lock);
		radix_tree_delete(&btnc->page_tree, newkey);
		spin_unlock_irq(&btnc->tree_lock);
		unlock_page(ctxt->bh->b_page);
	} else
		brelse(nbh);
}