#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct btrfs_trans_handle {scalar_t__ transid; } ;
struct TYPE_3__ {scalar_t__ objectid; } ;
struct btrfs_root {scalar_t__ last_trans; scalar_t__ commit_root; scalar_t__ node; int in_trans_setup; TYPE_2__* fs_info; TYPE_1__ root_key; scalar_t__ ref_cows; } ;
struct TYPE_4__ {int /*<<< orphan*/  fs_roots_radix_lock; int /*<<< orphan*/  fs_roots_radix; struct btrfs_root* extent_root; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_ROOT_TRANS_TAG ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  btrfs_init_reloc_root (struct btrfs_trans_handle*,struct btrfs_root*) ; 
 int /*<<< orphan*/  radix_tree_tag_set (int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int record_root_in_trans(struct btrfs_trans_handle *trans,
			       struct btrfs_root *root)
{
	if (root->ref_cows && root->last_trans < trans->transid) {
		WARN_ON(root == root->fs_info->extent_root);
		WARN_ON(root->commit_root != root->node);

		/*
		 * see below for in_trans_setup usage rules
		 * we have the reloc mutex held now, so there
		 * is only one writer in this function
		 */
		root->in_trans_setup = 1;

		/* make sure readers find in_trans_setup before
		 * they find our root->last_trans update
		 */
		smp_wmb();

		spin_lock(&root->fs_info->fs_roots_radix_lock);
		if (root->last_trans == trans->transid) {
			spin_unlock(&root->fs_info->fs_roots_radix_lock);
			return 0;
		}
		radix_tree_tag_set(&root->fs_info->fs_roots_radix,
			   (unsigned long)root->root_key.objectid,
			   BTRFS_ROOT_TRANS_TAG);
		spin_unlock(&root->fs_info->fs_roots_radix_lock);
		root->last_trans = trans->transid;

		/* this is pretty tricky.  We don't want to
		 * take the relocation lock in btrfs_record_root_in_trans
		 * unless we're really doing the first setup for this root in
		 * this transaction.
		 *
		 * Normally we'd use root->last_trans as a flag to decide
		 * if we want to take the expensive mutex.
		 *
		 * But, we have to set root->last_trans before we
		 * init the relocation root, otherwise, we trip over warnings
		 * in ctree.c.  The solution used here is to flag ourselves
		 * with root->in_trans_setup.  When this is 1, we're still
		 * fixing up the reloc trees and everyone must wait.
		 *
		 * When this is zero, they can trust root->last_trans and fly
		 * through btrfs_record_root_in_trans without having to take the
		 * lock.  smp_wmb() makes sure that all the writes above are
		 * done before we pop in the zero below
		 */
		btrfs_init_reloc_root(trans, root);
		smp_wmb();
		root->in_trans_setup = 0;
	}
	return 0;
}