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
struct btrfs_root {struct btrfs_free_space_ctl* free_ino_pinned; struct btrfs_free_space_ctl* free_ino_ctl; } ;
struct btrfs_free_space_ctl {int unit; int /*<<< orphan*/ * op; scalar_t__ extents_thresh; int /*<<< orphan*/ * private; scalar_t__ start; int /*<<< orphan*/  tree_lock; } ;

/* Variables and functions */
 scalar_t__ INIT_THRESHOLD ; 
 int /*<<< orphan*/  free_ino_op ; 
 int /*<<< orphan*/  pinned_free_ino_op ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void btrfs_init_free_ino_ctl(struct btrfs_root *root)
{
	struct btrfs_free_space_ctl *ctl = root->free_ino_ctl;
	struct btrfs_free_space_ctl *pinned = root->free_ino_pinned;

	spin_lock_init(&ctl->tree_lock);
	ctl->unit = 1;
	ctl->start = 0;
	ctl->private = NULL;
	ctl->op = &free_ino_op;

	/*
	 * Initially we allow to use 16K of ram to cache chunks of
	 * inode numbers before we resort to bitmaps. This is somewhat
	 * arbitrary, but it will be adjusted in runtime.
	 */
	ctl->extents_thresh = INIT_THRESHOLD;

	spin_lock_init(&pinned->tree_lock);
	pinned->unit = 1;
	pinned->start = 0;
	pinned->private = NULL;
	pinned->extents_thresh = 0;
	pinned->op = &pinned_free_ino_op;
}