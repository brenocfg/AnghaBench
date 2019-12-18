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
typedef  scalar_t__ u64 ;
struct btrfs_transaction {scalar_t__ blocked; int /*<<< orphan*/  transid; } ;
struct btrfs_trans_handle {int use_count; scalar_t__ bytes_reserved; int /*<<< orphan*/ * block_rsv; int /*<<< orphan*/  transid; scalar_t__ aborted; int /*<<< orphan*/ * orig_rsv; scalar_t__ delayed_ref_updates; scalar_t__ blocks_used; struct btrfs_transaction* transaction; } ;
struct btrfs_root {TYPE_1__* fs_info; } ;
struct TYPE_4__ {struct btrfs_trans_handle* journal_info; } ;
struct TYPE_3__ {int fs_state; int /*<<< orphan*/  trans_block_rsv; struct btrfs_transaction* running_transaction; int /*<<< orphan*/  sb; struct btrfs_root* chunk_root; } ;

/* Variables and functions */
 int BTRFS_SUPER_FLAG_ERROR ; 
 int EBUSY ; 
 int ENOMEM ; 
 int EROFS ; 
 struct btrfs_trans_handle* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int TRANS_JOIN ; 
 int TRANS_JOIN_NOLOCK ; 
 int TRANS_USERSPACE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int btrfs_block_rsv_add (struct btrfs_root*,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ btrfs_calc_trans_metadata_size (struct btrfs_root*,scalar_t__) ; 
 int /*<<< orphan*/  btrfs_commit_transaction (struct btrfs_trans_handle*,struct btrfs_root*) ; 
 int /*<<< orphan*/  btrfs_record_root_in_trans (struct btrfs_trans_handle*,struct btrfs_root*) ; 
 int /*<<< orphan*/  btrfs_trans_handle_cachep ; 
 TYPE_2__* current ; 
 int join_transaction (struct btrfs_root*,int) ; 
 struct btrfs_trans_handle* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct btrfs_trans_handle*) ; 
 scalar_t__ may_wait_transaction (struct btrfs_root*,int) ; 
 int /*<<< orphan*/  sb_end_intwrite (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sb_start_intwrite (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  trace_btrfs_space_reservation (TYPE_1__*,char*,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  wait_current_trans (struct btrfs_root*) ; 

__attribute__((used)) static struct btrfs_trans_handle *start_transaction(struct btrfs_root *root,
						    u64 num_items, int type)
{
	struct btrfs_trans_handle *h;
	struct btrfs_transaction *cur_trans;
	u64 num_bytes = 0;
	int ret;

	if (root->fs_info->fs_state & BTRFS_SUPER_FLAG_ERROR)
		return ERR_PTR(-EROFS);

	if (current->journal_info) {
		WARN_ON(type != TRANS_JOIN && type != TRANS_JOIN_NOLOCK);
		h = current->journal_info;
		h->use_count++;
		h->orig_rsv = h->block_rsv;
		h->block_rsv = NULL;
		goto got_it;
	}

	/*
	 * Do the reservation before we join the transaction so we can do all
	 * the appropriate flushing if need be.
	 */
	if (num_items > 0 && root != root->fs_info->chunk_root) {
		num_bytes = btrfs_calc_trans_metadata_size(root, num_items);
		ret = btrfs_block_rsv_add(root,
					  &root->fs_info->trans_block_rsv,
					  num_bytes);
		if (ret)
			return ERR_PTR(ret);
	}
again:
	h = kmem_cache_alloc(btrfs_trans_handle_cachep, GFP_NOFS);
	if (!h)
		return ERR_PTR(-ENOMEM);

	sb_start_intwrite(root->fs_info->sb);

	if (may_wait_transaction(root, type))
		wait_current_trans(root);

	do {
		ret = join_transaction(root, type == TRANS_JOIN_NOLOCK);
		if (ret == -EBUSY)
			wait_current_trans(root);
	} while (ret == -EBUSY);

	if (ret < 0) {
		sb_end_intwrite(root->fs_info->sb);
		kmem_cache_free(btrfs_trans_handle_cachep, h);
		return ERR_PTR(ret);
	}

	cur_trans = root->fs_info->running_transaction;

	h->transid = cur_trans->transid;
	h->transaction = cur_trans;
	h->blocks_used = 0;
	h->bytes_reserved = 0;
	h->delayed_ref_updates = 0;
	h->use_count = 1;
	h->block_rsv = NULL;
	h->orig_rsv = NULL;
	h->aborted = 0;

	smp_mb();
	if (cur_trans->blocked && may_wait_transaction(root, type)) {
		btrfs_commit_transaction(h, root);
		goto again;
	}

	if (num_bytes) {
		trace_btrfs_space_reservation(root->fs_info, "transaction",
					      h->transid, num_bytes, 1);
		h->block_rsv = &root->fs_info->trans_block_rsv;
		h->bytes_reserved = num_bytes;
	}

got_it:
	btrfs_record_root_in_trans(h, root);

	if (!current->journal_info && type != TRANS_USERSPACE)
		current->journal_info = h;
	return h;
}