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
struct ext3_super_block {int /*<<< orphan*/  s_state; } ;
typedef  int /*<<< orphan*/  journal_t ;
struct TYPE_2__ {int /*<<< orphan*/  s_mount_opt; int /*<<< orphan*/ * s_journal; int /*<<< orphan*/  s_mount_state; struct ext3_super_block* s_es; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ERRORS_CONT ; 
 int /*<<< orphan*/  ERRORS_PANIC ; 
 int /*<<< orphan*/  ERRORS_RO ; 
 int /*<<< orphan*/  EXT3_ERROR_FS ; 
 int /*<<< orphan*/  EXT3_MOUNT_ABORT ; 
 TYPE_1__* EXT3_SB (struct super_block*) ; 
 int /*<<< orphan*/  KERN_CRIT ; 
 int MS_RDONLY ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext3_commit_super (struct super_block*,struct ext3_super_block*,int) ; 
 int /*<<< orphan*/  ext3_msg (struct super_block*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  journal_abort (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_opt (struct super_block*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ext3_handle_error(struct super_block *sb)
{
	struct ext3_super_block *es = EXT3_SB(sb)->s_es;

	EXT3_SB(sb)->s_mount_state |= EXT3_ERROR_FS;
	es->s_state |= cpu_to_le16(EXT3_ERROR_FS);

	if (sb->s_flags & MS_RDONLY)
		return;

	if (!test_opt (sb, ERRORS_CONT)) {
		journal_t *journal = EXT3_SB(sb)->s_journal;

		EXT3_SB(sb)->s_mount_opt |= EXT3_MOUNT_ABORT;
		if (journal)
			journal_abort(journal, -EIO);
	}
	if (test_opt (sb, ERRORS_RO)) {
		ext3_msg(sb, KERN_CRIT,
			"error: remounting filesystem read-only");
		sb->s_flags |= MS_RDONLY;
	}
	ext3_commit_super(sb, es, 1);
	if (test_opt(sb, ERRORS_PANIC))
		panic("EXT3-fs (%s): panic forced after error\n",
			sb->s_id);
}