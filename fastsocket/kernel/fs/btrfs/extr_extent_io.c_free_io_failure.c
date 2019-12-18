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
struct io_failure_record {scalar_t__ len; scalar_t__ start; } ;
struct inode {int dummy; } ;
struct extent_io_tree {int dummy; } ;
struct TYPE_2__ {struct extent_io_tree io_tree; struct extent_io_tree io_failure_tree; } ;

/* Variables and functions */
 TYPE_1__* BTRFS_I (struct inode*) ; 
 int EXTENT_DAMAGED ; 
 int EXTENT_DIRTY ; 
 int EXTENT_LOCKED ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int clear_extent_bits (struct extent_io_tree*,scalar_t__,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct io_failure_record*) ; 
 int /*<<< orphan*/  set_state_private (struct extent_io_tree*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int free_io_failure(struct inode *inode, struct io_failure_record *rec,
				int did_repair)
{
	int ret;
	int err = 0;
	struct extent_io_tree *failure_tree = &BTRFS_I(inode)->io_failure_tree;

	set_state_private(failure_tree, rec->start, 0);
	ret = clear_extent_bits(failure_tree, rec->start,
				rec->start + rec->len - 1,
				EXTENT_LOCKED | EXTENT_DIRTY, GFP_NOFS);
	if (ret)
		err = ret;

	if (did_repair) {
		ret = clear_extent_bits(&BTRFS_I(inode)->io_tree, rec->start,
					rec->start + rec->len - 1,
					EXTENT_DAMAGED, GFP_NOFS);
		if (ret && !err)
			err = ret;
	}

	kfree(rec);
	return err;
}