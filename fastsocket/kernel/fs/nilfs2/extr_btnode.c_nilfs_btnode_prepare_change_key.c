#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct nilfs_btnode_chkey_ctxt {scalar_t__ oldkey; scalar_t__ newkey; struct buffer_head* newbh; struct buffer_head* bh; } ;
struct inode {scalar_t__ i_blkbits; } ;
struct buffer_head {TYPE_1__* b_page; } ;
struct address_space {int /*<<< orphan*/  tree_lock; int /*<<< orphan*/  page_tree; } ;
typedef  scalar_t__ __u64 ;
struct TYPE_5__ {scalar_t__ index; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EEXIST ; 
 int GFP_NOFS ; 
 struct inode* NILFS_BTNC_I (struct address_space*) ; 
 int /*<<< orphan*/  NILFS_PAGE_BUG (TYPE_1__*,char*,unsigned long long,unsigned long long) ; 
 scalar_t__ PAGE_CACHE_SHIFT ; 
 int __GFP_HIGHMEM ; 
 int invalidate_inode_pages2_range (struct address_space*,scalar_t__,scalar_t__) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  lock_page (TYPE_1__*) ; 
 int nilfs_btnode_get (struct address_space*,scalar_t__,int /*<<< orphan*/ ,struct buffer_head**,int) ; 
 int radix_tree_insert (int /*<<< orphan*/ *,scalar_t__,TYPE_1__*) ; 
 int radix_tree_preload (int) ; 
 int /*<<< orphan*/  radix_tree_preload_end () ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_page (TYPE_1__*) ; 

int nilfs_btnode_prepare_change_key(struct address_space *btnc,
				    struct nilfs_btnode_chkey_ctxt *ctxt)
{
	struct buffer_head *obh, *nbh;
	struct inode *inode = NILFS_BTNC_I(btnc);
	__u64 oldkey = ctxt->oldkey, newkey = ctxt->newkey;
	int err;

	if (oldkey == newkey)
		return 0;

	obh = ctxt->bh;
	ctxt->newbh = NULL;

	if (inode->i_blkbits == PAGE_CACHE_SHIFT) {
		lock_page(obh->b_page);
		/*
		 * We cannot call radix_tree_preload for the kernels older
		 * than 2.6.23, because it is not exported for modules.
		 */
retry:
		err = radix_tree_preload(GFP_NOFS & ~__GFP_HIGHMEM);
		if (err)
			goto failed_unlock;
		/* BUG_ON(oldkey != obh->b_page->index); */
		if (unlikely(oldkey != obh->b_page->index))
			NILFS_PAGE_BUG(obh->b_page,
				       "invalid oldkey %lld (newkey=%lld)",
				       (unsigned long long)oldkey,
				       (unsigned long long)newkey);

		spin_lock_irq(&btnc->tree_lock);
		err = radix_tree_insert(&btnc->page_tree, newkey, obh->b_page);
		spin_unlock_irq(&btnc->tree_lock);
		/*
		 * Note: page->index will not change to newkey until
		 * nilfs_btnode_commit_change_key() will be called.
		 * To protect the page in intermediate state, the page lock
		 * is held.
		 */
		radix_tree_preload_end();
		if (!err)
			return 0;
		else if (err != -EEXIST)
			goto failed_unlock;

		err = invalidate_inode_pages2_range(btnc, newkey, newkey);
		if (!err)
			goto retry;
		/* fallback to copy mode */
		unlock_page(obh->b_page);
	}

	err = nilfs_btnode_get(btnc, newkey, 0, &nbh, 1);
	if (likely(!err)) {
		BUG_ON(nbh == obh);
		ctxt->newbh = nbh;
	}
	return err;

 failed_unlock:
	unlock_page(obh->b_page);
	return err;
}