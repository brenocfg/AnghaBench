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
struct super_block {int /*<<< orphan*/  s_flags; void* s_magic; } ;
struct nilfs_super_block {int /*<<< orphan*/  s_c_block_max; int /*<<< orphan*/  s_c_interval; int /*<<< orphan*/  s_def_resgid; int /*<<< orphan*/  s_def_resuid; int /*<<< orphan*/  s_magic; } ;
struct nilfs_sb_info {void* s_watermark; void* s_interval; void* s_resgid; void* s_resuid; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MS_NOATIME ; 
 struct nilfs_sb_info* NILFS_SB (struct super_block*) ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nilfs_set_default_options (struct nilfs_sb_info*,struct nilfs_super_block*) ; 
 int /*<<< orphan*/  parse_options (char*,struct super_block*) ; 

int nilfs_store_magic_and_option(struct super_block *sb,
				 struct nilfs_super_block *sbp,
				 char *data)
{
	struct nilfs_sb_info *sbi = NILFS_SB(sb);

	sb->s_magic = le16_to_cpu(sbp->s_magic);

	/* FS independent flags */
#ifdef NILFS_ATIME_DISABLE
	sb->s_flags |= MS_NOATIME;
#endif

	nilfs_set_default_options(sbi, sbp);

	sbi->s_resuid = le16_to_cpu(sbp->s_def_resuid);
	sbi->s_resgid = le16_to_cpu(sbp->s_def_resgid);
	sbi->s_interval = le32_to_cpu(sbp->s_c_interval);
	sbi->s_watermark = le32_to_cpu(sbp->s_c_block_max);

	return !parse_options(data, sb) ? -EINVAL : 0 ;
}