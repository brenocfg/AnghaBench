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
struct TYPE_2__ {scalar_t__ flushing; } ;
struct btrfs_transaction {TYPE_1__ delayed_refs; scalar_t__ blocked; } ;
struct btrfs_trans_handle {int delayed_ref_updates; struct btrfs_block_rsv* block_rsv; struct btrfs_transaction* transaction; } ;
struct btrfs_root {int dummy; } ;
struct btrfs_block_rsv {int dummy; } ;

/* Variables and functions */
 int btrfs_run_delayed_refs (struct btrfs_trans_handle*,struct btrfs_root*,int) ; 
 int should_end_transaction (struct btrfs_trans_handle*,struct btrfs_root*) ; 
 int /*<<< orphan*/  smp_mb () ; 

int btrfs_should_end_transaction(struct btrfs_trans_handle *trans,
				 struct btrfs_root *root)
{
	struct btrfs_transaction *cur_trans = trans->transaction;
	struct btrfs_block_rsv *rsv = trans->block_rsv;
	int updates;
	int err;

	smp_mb();
	if (cur_trans->blocked || cur_trans->delayed_refs.flushing)
		return 1;

	/*
	 * We need to do this in case we're deleting csums so the global block
	 * rsv get's used instead of the csum block rsv.
	 */
	trans->block_rsv = NULL;

	updates = trans->delayed_ref_updates;
	trans->delayed_ref_updates = 0;
	if (updates) {
		err = btrfs_run_delayed_refs(trans, root, updates);
		if (err) /* Error code will also eval true */
			return err;
	}

	trans->block_rsv = rsv;

	return should_end_transaction(trans, root);
}