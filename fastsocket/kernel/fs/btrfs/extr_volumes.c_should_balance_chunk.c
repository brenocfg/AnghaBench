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
typedef  int u64 ;
struct extent_buffer {int dummy; } ;
struct btrfs_root {TYPE_1__* fs_info; } ;
struct btrfs_chunk {int dummy; } ;
struct btrfs_balance_args {int flags; } ;
struct btrfs_balance_control {int flags; int /*<<< orphan*/  fs_info; struct btrfs_balance_args meta; struct btrfs_balance_args sys; struct btrfs_balance_args data; } ;
struct TYPE_2__ {struct btrfs_balance_control* balance_ctl; } ;

/* Variables and functions */
 int BTRFS_BALANCE_ARGS_DEVID ; 
 int BTRFS_BALANCE_ARGS_DRANGE ; 
 int BTRFS_BALANCE_ARGS_PROFILES ; 
 int BTRFS_BALANCE_ARGS_SOFT ; 
 int BTRFS_BALANCE_ARGS_USAGE ; 
 int BTRFS_BALANCE_ARGS_VRANGE ; 
 int BTRFS_BALANCE_TYPE_MASK ; 
 int BTRFS_BLOCK_GROUP_DATA ; 
 int BTRFS_BLOCK_GROUP_METADATA ; 
 int BTRFS_BLOCK_GROUP_SYSTEM ; 
 int BTRFS_BLOCK_GROUP_TYPE_MASK ; 
 int btrfs_chunk_type (struct extent_buffer*,struct btrfs_chunk*) ; 
 scalar_t__ chunk_devid_filter (struct extent_buffer*,struct btrfs_chunk*,struct btrfs_balance_args*) ; 
 scalar_t__ chunk_drange_filter (struct extent_buffer*,struct btrfs_chunk*,int,struct btrfs_balance_args*) ; 
 scalar_t__ chunk_profiles_filter (int,struct btrfs_balance_args*) ; 
 scalar_t__ chunk_soft_convert_filter (int,struct btrfs_balance_args*) ; 
 scalar_t__ chunk_usage_filter (int /*<<< orphan*/ ,int,struct btrfs_balance_args*) ; 
 scalar_t__ chunk_vrange_filter (struct extent_buffer*,struct btrfs_chunk*,int,struct btrfs_balance_args*) ; 

__attribute__((used)) static int should_balance_chunk(struct btrfs_root *root,
				struct extent_buffer *leaf,
				struct btrfs_chunk *chunk, u64 chunk_offset)
{
	struct btrfs_balance_control *bctl = root->fs_info->balance_ctl;
	struct btrfs_balance_args *bargs = NULL;
	u64 chunk_type = btrfs_chunk_type(leaf, chunk);

	/* type filter */
	if (!((chunk_type & BTRFS_BLOCK_GROUP_TYPE_MASK) &
	      (bctl->flags & BTRFS_BALANCE_TYPE_MASK))) {
		return 0;
	}

	if (chunk_type & BTRFS_BLOCK_GROUP_DATA)
		bargs = &bctl->data;
	else if (chunk_type & BTRFS_BLOCK_GROUP_SYSTEM)
		bargs = &bctl->sys;
	else if (chunk_type & BTRFS_BLOCK_GROUP_METADATA)
		bargs = &bctl->meta;

	/* profiles filter */
	if ((bargs->flags & BTRFS_BALANCE_ARGS_PROFILES) &&
	    chunk_profiles_filter(chunk_type, bargs)) {
		return 0;
	}

	/* usage filter */
	if ((bargs->flags & BTRFS_BALANCE_ARGS_USAGE) &&
	    chunk_usage_filter(bctl->fs_info, chunk_offset, bargs)) {
		return 0;
	}

	/* devid filter */
	if ((bargs->flags & BTRFS_BALANCE_ARGS_DEVID) &&
	    chunk_devid_filter(leaf, chunk, bargs)) {
		return 0;
	}

	/* drange filter, makes sense only with devid filter */
	if ((bargs->flags & BTRFS_BALANCE_ARGS_DRANGE) &&
	    chunk_drange_filter(leaf, chunk, chunk_offset, bargs)) {
		return 0;
	}

	/* vrange filter */
	if ((bargs->flags & BTRFS_BALANCE_ARGS_VRANGE) &&
	    chunk_vrange_filter(leaf, chunk, chunk_offset, bargs)) {
		return 0;
	}

	/* soft profile changing mode */
	if ((bargs->flags & BTRFS_BALANCE_ARGS_SOFT) &&
	    chunk_soft_convert_filter(chunk_type, bargs)) {
		return 0;
	}

	return 1;
}