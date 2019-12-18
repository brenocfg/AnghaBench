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
struct super_block {int s_flags; int /*<<< orphan*/  s_id; } ;
struct ext4_super_block {int /*<<< orphan*/  s_state; } ;
typedef  int /*<<< orphan*/  journal_t ;
struct TYPE_2__ {int /*<<< orphan*/  s_mount_flags; int /*<<< orphan*/ * s_journal; int /*<<< orphan*/  s_mount_state; struct ext4_super_block* s_es; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ERRORS_CONT ; 
 int /*<<< orphan*/  ERRORS_PANIC ; 
 int /*<<< orphan*/  ERRORS_RO ; 
 int /*<<< orphan*/  EXT4_ERROR_FS ; 
 int /*<<< orphan*/  EXT4_MF_FS_ABORTED ; 
 TYPE_1__* EXT4_SB (struct super_block*) ; 
 int /*<<< orphan*/  KERN_CRIT ; 
 int MS_RDONLY ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_commit_super (struct super_block*,int) ; 
 int /*<<< orphan*/  ext4_msg (struct super_block*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  jbd2_journal_abort (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_opt (struct super_block*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ext4_handle_error(struct super_block *sb)
{
	struct ext4_super_block *es = EXT4_SB(sb)->s_es;

	EXT4_SB(sb)->s_mount_state |= EXT4_ERROR_FS;
	es->s_state |= cpu_to_le16(EXT4_ERROR_FS);

	if (sb->s_flags & MS_RDONLY)
		return;

	if (!test_opt(sb, ERRORS_CONT)) {
		journal_t *journal = EXT4_SB(sb)->s_journal;

		EXT4_SB(sb)->s_mount_flags |= EXT4_MF_FS_ABORTED;
		if (journal)
			jbd2_journal_abort(journal, -EIO);
	}
	if (test_opt(sb, ERRORS_RO)) {
		ext4_msg(sb, KERN_CRIT, "Remounting filesystem read-only");
		sb->s_flags |= MS_RDONLY;
	}
	ext4_commit_super(sb, 1);
	if (test_opt(sb, ERRORS_PANIC))
		panic("EXT4-fs (device %s): panic forced after error\n",
			sb->s_id);
}