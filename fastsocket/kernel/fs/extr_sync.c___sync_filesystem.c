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
struct super_block {int /*<<< orphan*/  s_bdev; TYPE_1__* s_op; int /*<<< orphan*/  s_bdi; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* sync_fs ) (struct super_block*,int) ;} ;

/* Variables and functions */
 int __sync_blockdev (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct super_block*,int) ; 
 int /*<<< orphan*/  sync_inodes_sb (struct super_block*) ; 
 int /*<<< orphan*/  sync_quota_sb (struct super_block*,int) ; 
 int /*<<< orphan*/  writeback_inodes_sb (struct super_block*) ; 
 int /*<<< orphan*/  writeout_quota_sb (struct super_block*,int) ; 

__attribute__((used)) static int __sync_filesystem(struct super_block *sb, int wait)
{
	/*
	 * This should be safe, as we require bdi backing to actually
	 * write out data in the first place
	 */
	if (!sb->s_bdi)
		return 0;

	/* Avoid doing twice syncing and cache pruning for quota sync */
	if (!wait) {
		writeout_quota_sb(sb, -1);
		writeback_inodes_sb(sb);
	} else {
		sync_quota_sb(sb, -1);
		sync_inodes_sb(sb);
	}
	if (sb->s_op->sync_fs)
		sb->s_op->sync_fs(sb, wait);
	return __sync_blockdev(sb->s_bdev, wait);
}