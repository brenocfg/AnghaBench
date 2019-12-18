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
typedef  scalar_t__ uint ;
struct super_block {int dummy; } ;
struct jfs_superblock {int s_state; int s_logdev; int s_logserial; int s_flag; } ;
struct jfs_sb_info {int flag; scalar_t__ p_state; scalar_t__ state; TYPE_2__* log; } ;
struct buffer_head {scalar_t__ b_data; } ;
struct TYPE_4__ {scalar_t__ serial; TYPE_1__* bdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  bd_dev; } ;

/* Variables and functions */
 scalar_t__ FM_CLEAN ; 
 scalar_t__ FM_DIRTY ; 
 scalar_t__ FM_MOUNT ; 
 scalar_t__ JFS_DASD_ENABLED ; 
 scalar_t__ JFS_DASD_PRIME ; 
 int JFS_NOINTEGRITY ; 
 struct jfs_sb_info* JFS_SBI (struct super_block*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int cpu_to_le32 (scalar_t__) ; 
 int /*<<< orphan*/  jfs_err (char*) ; 
 int /*<<< orphan*/  mark_buffer_dirty (struct buffer_head*) ; 
 scalar_t__ new_encode_dev (int /*<<< orphan*/ ) ; 
 int readSuper (struct super_block*,struct buffer_head**) ; 
 int /*<<< orphan*/  sync_dirty_buffer (struct buffer_head*) ; 

int updateSuper(struct super_block *sb, uint state)
{
	struct jfs_superblock *j_sb;
	struct jfs_sb_info *sbi = JFS_SBI(sb);
	struct buffer_head *bh;
	int rc;

	if (sbi->flag & JFS_NOINTEGRITY) {
		if (state == FM_DIRTY) {
			sbi->p_state = state;
			return 0;
		} else if (state == FM_MOUNT) {
			sbi->p_state = sbi->state;
			state = FM_DIRTY;
		} else if (state == FM_CLEAN) {
			state = sbi->p_state;
		} else
			jfs_err("updateSuper: bad state");
	} else if (sbi->state == FM_DIRTY)
		return 0;

	if ((rc = readSuper(sb, &bh)))
		return rc;

	j_sb = (struct jfs_superblock *)bh->b_data;

	j_sb->s_state = cpu_to_le32(state);
	sbi->state = state;

	if (state == FM_MOUNT) {
		/* record log's dev_t and mount serial number */
		j_sb->s_logdev = cpu_to_le32(new_encode_dev(sbi->log->bdev->bd_dev));
		j_sb->s_logserial = cpu_to_le32(sbi->log->serial);
	} else if (state == FM_CLEAN) {
		/*
		 * If this volume is shared with OS/2, OS/2 will need to
		 * recalculate DASD usage, since we don't deal with it.
		 */
		if (j_sb->s_flag & cpu_to_le32(JFS_DASD_ENABLED))
			j_sb->s_flag |= cpu_to_le32(JFS_DASD_PRIME);
	}

	mark_buffer_dirty(bh);
	sync_dirty_buffer(bh);
	brelse(bh);

	return 0;
}