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
struct btrfs_free_space_ctl {int extents_thresh; int /*<<< orphan*/ * op; struct btrfs_block_group_cache* private; int /*<<< orphan*/  start; int /*<<< orphan*/  unit; int /*<<< orphan*/  tree_lock; } ;
struct btrfs_free_space {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  objectid; } ;
struct btrfs_block_group_cache {TYPE_1__ key; int /*<<< orphan*/  sectorsize; struct btrfs_free_space_ctl* free_space_ctl; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_space_op ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void btrfs_init_free_space_ctl(struct btrfs_block_group_cache *block_group)
{
	struct btrfs_free_space_ctl *ctl = block_group->free_space_ctl;

	spin_lock_init(&ctl->tree_lock);
	ctl->unit = block_group->sectorsize;
	ctl->start = block_group->key.objectid;
	ctl->private = block_group;
	ctl->op = &free_space_op;

	/*
	 * we only want to have 32k of ram per block group for keeping
	 * track of free space, and if we pass 1/2 of that we want to
	 * start converting things over to using bitmaps
	 */
	ctl->extents_thresh = ((1024 * 32) / 2) /
				sizeof(struct btrfs_free_space);
}