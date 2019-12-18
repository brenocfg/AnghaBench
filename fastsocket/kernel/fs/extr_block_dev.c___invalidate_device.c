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
struct super_block {int dummy; } ;
struct block_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drop_super (struct super_block*) ; 
 struct super_block* get_super (struct block_device*) ; 
 int /*<<< orphan*/  invalidate_bdev (struct block_device*) ; 
 int invalidate_inodes (struct super_block*,int) ; 
 int /*<<< orphan*/  shrink_dcache_sb (struct super_block*) ; 

int __invalidate_device(struct block_device *bdev, bool kill_dirty)
{
	struct super_block *sb = get_super(bdev);
	int res = 0;

	if (sb) {
		/*
		 * no need to lock the super, get_super holds the
		 * read mutex so the filesystem cannot go away
		 * under us (->put_super runs with the write lock
		 * hold).
		 */
		shrink_dcache_sb(sb);
		res = invalidate_inodes(sb, kill_dirty);
		drop_super(sb);
	}
	invalidate_bdev(bdev);
	return res;
}