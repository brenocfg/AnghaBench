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
struct super_block {int s_flags; } ;
struct ext3_super_block {int /*<<< orphan*/  s_journal_inum; } ;
typedef  int /*<<< orphan*/  journal_t ;
struct TYPE_2__ {int /*<<< orphan*/ * s_journal; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int EROFS ; 
 int /*<<< orphan*/  EXT3_FEATURE_COMPAT_HAS_JOURNAL ; 
 int /*<<< orphan*/  EXT3_FEATURE_INCOMPAT_RECOVER ; 
 TYPE_1__* EXT3_SB (struct super_block*) ; 
 int /*<<< orphan*/  EXT3_SET_COMPAT_FEATURE (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXT3_SET_INCOMPAT_FEATURE (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int MS_RDONLY ; 
 int /*<<< orphan*/  cpu_to_le32 (unsigned int) ; 
 int /*<<< orphan*/  ext3_commit_super (struct super_block*,struct ext3_super_block*,int) ; 
 int /*<<< orphan*/ * ext3_get_journal (struct super_block*,unsigned int) ; 
 int /*<<< orphan*/  ext3_msg (struct super_block*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ext3_update_dynamic_rev (struct super_block*) ; 
 int journal_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  journal_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ext3_create_journal(struct super_block *sb,
			       struct ext3_super_block *es,
			       unsigned int journal_inum)
{
	journal_t *journal;
	int err;

	if (sb->s_flags & MS_RDONLY) {
		ext3_msg(sb, KERN_ERR,
			"error: readonly filesystem when trying to "
			"create journal");
		return -EROFS;
	}

	journal = ext3_get_journal(sb, journal_inum);
	if (!journal)
		return -EINVAL;

	ext3_msg(sb, KERN_INFO, "creating new journal on inode %u",
	       journal_inum);

	err = journal_create(journal);
	if (err) {
		ext3_msg(sb, KERN_ERR, "error creating journal");
		journal_destroy(journal);
		return -EIO;
	}

	EXT3_SB(sb)->s_journal = journal;

	ext3_update_dynamic_rev(sb);
	EXT3_SET_INCOMPAT_FEATURE(sb, EXT3_FEATURE_INCOMPAT_RECOVER);
	EXT3_SET_COMPAT_FEATURE(sb, EXT3_FEATURE_COMPAT_HAS_JOURNAL);

	es->s_journal_inum = cpu_to_le32(journal_inum);

	/* Make sure we flush the recovery flag to disk. */
	ext3_commit_super(sb, es, 1);

	return 0;
}