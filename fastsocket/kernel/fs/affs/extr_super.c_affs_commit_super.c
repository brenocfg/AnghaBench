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
struct buffer_head {int dummy; } ;
struct affs_sb_info {struct buffer_head* s_root_bh; } ;
struct affs_root_tail {int /*<<< orphan*/  disk_change; int /*<<< orphan*/  bm_flag; } ;

/* Variables and functions */
 struct affs_root_tail* AFFS_ROOT_TAIL (struct super_block*,struct buffer_head*) ; 
 struct affs_sb_info* AFFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  affs_fix_checksum (struct super_block*,struct buffer_head*) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int /*<<< orphan*/  get_seconds () ; 
 int /*<<< orphan*/  mark_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  secs_to_datestamp (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
affs_commit_super(struct super_block *sb, int clean)
{
	struct affs_sb_info *sbi = AFFS_SB(sb);
	struct buffer_head *bh = sbi->s_root_bh;
	struct affs_root_tail *tail = AFFS_ROOT_TAIL(sb, bh);

	tail->bm_flag = cpu_to_be32(clean);
	secs_to_datestamp(get_seconds(), &tail->disk_change);
	affs_fix_checksum(sb, bh);
	mark_buffer_dirty(bh);
}