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
struct super_block {int /*<<< orphan*/  s_blocksize; } ;
struct ext3_super_block {int /*<<< orphan*/  s_mtime; int /*<<< orphan*/  s_mnt_count; int /*<<< orphan*/  s_max_mnt_count; int /*<<< orphan*/  s_state; int /*<<< orphan*/  s_checkinterval; int /*<<< orphan*/  s_lastcheck; int /*<<< orphan*/  s_rev_level; } ;
struct ext3_sb_info {int s_mount_state; TYPE_1__* s_journal; int /*<<< orphan*/  s_mount_opt; int /*<<< orphan*/  s_groups_count; } ;
typedef  scalar_t__ __s16 ;
struct TYPE_2__ {int /*<<< orphan*/  j_dev; int /*<<< orphan*/ * j_inode; } ;

/* Variables and functions */
 int BDEVNAME_SIZE ; 
 int /*<<< orphan*/  DEBUG ; 
 int /*<<< orphan*/  EXT3_BLOCKS_PER_GROUP (struct super_block*) ; 
 int EXT3_DFL_MAX_MNT_COUNT ; 
 int EXT3_ERROR_FS ; 
 int /*<<< orphan*/  EXT3_FEATURE_INCOMPAT_RECOVER ; 
 int /*<<< orphan*/  EXT3_INODES_PER_GROUP (struct super_block*) ; 
 scalar_t__ EXT3_MAX_SUPP_REV ; 
 struct ext3_sb_info* EXT3_SB (struct super_block*) ; 
 int /*<<< orphan*/  EXT3_SET_INCOMPAT_FEATURE (struct super_block*,int /*<<< orphan*/ ) ; 
 int EXT3_VALID_FS ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int MS_RDONLY ; 
 int /*<<< orphan*/  bdevname (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (scalar_t__) ; 
 int /*<<< orphan*/  ext3_commit_super (struct super_block*,struct ext3_super_block*,int) ; 
 int /*<<< orphan*/  ext3_msg (struct super_block*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ext3_update_dynamic_rev (struct super_block*) ; 
 scalar_t__ get_seconds () ; 
 int /*<<< orphan*/  le16_add_cpu (int /*<<< orphan*/ *,int) ; 
 unsigned short le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ test_opt (struct super_block*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ext3_setup_super(struct super_block *sb, struct ext3_super_block *es,
			    int read_only)
{
	struct ext3_sb_info *sbi = EXT3_SB(sb);
	int res = 0;

	if (le32_to_cpu(es->s_rev_level) > EXT3_MAX_SUPP_REV) {
		ext3_msg(sb, KERN_ERR,
			"error: revision level too high, "
			"forcing read-only mode");
		res = MS_RDONLY;
	}
	if (read_only)
		return res;
	if (!(sbi->s_mount_state & EXT3_VALID_FS))
		ext3_msg(sb, KERN_WARNING,
			"warning: mounting unchecked fs, "
			"running e2fsck is recommended");
	else if ((sbi->s_mount_state & EXT3_ERROR_FS))
		ext3_msg(sb, KERN_WARNING,
			"warning: mounting fs with errors, "
			"running e2fsck is recommended");
	else if ((__s16) le16_to_cpu(es->s_max_mnt_count) >= 0 &&
		 le16_to_cpu(es->s_mnt_count) >=
		 (unsigned short) (__s16) le16_to_cpu(es->s_max_mnt_count))
		ext3_msg(sb, KERN_WARNING,
			"warning: maximal mount count reached, "
			"running e2fsck is recommended");
	else if (le32_to_cpu(es->s_checkinterval) &&
		(le32_to_cpu(es->s_lastcheck) +
			le32_to_cpu(es->s_checkinterval) <= get_seconds()))
		ext3_msg(sb, KERN_WARNING,
			"warning: checktime reached, "
			"running e2fsck is recommended");
#if 0
		/* @@@ We _will_ want to clear the valid bit if we find
                   inconsistencies, to force a fsck at reboot.  But for
                   a plain journaled filesystem we can keep it set as
                   valid forever! :) */
	es->s_state &= cpu_to_le16(~EXT3_VALID_FS);
#endif
	if (!(__s16) le16_to_cpu(es->s_max_mnt_count))
		es->s_max_mnt_count = cpu_to_le16(EXT3_DFL_MAX_MNT_COUNT);
	le16_add_cpu(&es->s_mnt_count, 1);
	es->s_mtime = cpu_to_le32(get_seconds());
	ext3_update_dynamic_rev(sb);
	EXT3_SET_INCOMPAT_FEATURE(sb, EXT3_FEATURE_INCOMPAT_RECOVER);

	ext3_commit_super(sb, es, 1);
	if (test_opt(sb, DEBUG))
		ext3_msg(sb, KERN_INFO, "[bs=%lu, gc=%lu, "
				"bpg=%lu, ipg=%lu, mo=%04lx]",
			sb->s_blocksize,
			sbi->s_groups_count,
			EXT3_BLOCKS_PER_GROUP(sb),
			EXT3_INODES_PER_GROUP(sb),
			sbi->s_mount_opt);

	if (EXT3_SB(sb)->s_journal->j_inode == NULL) {
		char b[BDEVNAME_SIZE];
		ext3_msg(sb, KERN_INFO, "using external journal on %s",
			bdevname(EXT3_SB(sb)->s_journal->j_dev, b));
	} else {
		ext3_msg(sb, KERN_INFO, "using internal journal");
	}
	return res;
}