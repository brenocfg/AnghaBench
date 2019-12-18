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
struct btrfs_free_space_ctl {TYPE_1__* op; int /*<<< orphan*/  total_bitmaps; } ;
struct btrfs_free_space {int /*<<< orphan*/  bitmap; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* recalc_thresholds ) (struct btrfs_free_space_ctl*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  btrfs_free_space_cachep ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct btrfs_free_space*) ; 
 int /*<<< orphan*/  stub1 (struct btrfs_free_space_ctl*) ; 
 int /*<<< orphan*/  unlink_free_space (struct btrfs_free_space_ctl*,struct btrfs_free_space*) ; 

__attribute__((used)) static void free_bitmap(struct btrfs_free_space_ctl *ctl,
			struct btrfs_free_space *bitmap_info)
{
	unlink_free_space(ctl, bitmap_info);
	kfree(bitmap_info->bitmap);
	kmem_cache_free(btrfs_free_space_cachep, bitmap_info);
	ctl->total_bitmaps--;
	ctl->op->recalc_thresholds(ctl);
}