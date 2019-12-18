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
struct ext3_super_block {void* s_free_inodes_count; void* s_free_blocks_count; void* s_wtime; } ;
struct buffer_head {int dummy; } ;
struct TYPE_2__ {struct buffer_head* s_sbh; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFER_TRACE (struct buffer_head*,char*) ; 
 TYPE_1__* EXT3_SB (struct super_block*) ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int MS_RDONLY ; 
 scalar_t__ buffer_write_io_error (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_buffer_write_io_error (struct buffer_head*) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext3_count_free_blocks (struct super_block*) ; 
 int /*<<< orphan*/  ext3_count_free_inodes (struct super_block*) ; 
 int /*<<< orphan*/  ext3_msg (struct super_block*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  get_seconds () ; 
 int /*<<< orphan*/  mark_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  set_buffer_uptodate (struct buffer_head*) ; 
 int sync_dirty_buffer (struct buffer_head*) ; 

__attribute__((used)) static int ext3_commit_super(struct super_block *sb,
			       struct ext3_super_block *es,
			       int sync)
{
	struct buffer_head *sbh = EXT3_SB(sb)->s_sbh;
	int error = 0;

	if (!sbh)
		return error;

	if (buffer_write_io_error(sbh)) {
		/*
		 * Oh, dear.  A previous attempt to write the
		 * superblock failed.  This could happen because the
		 * USB device was yanked out.  Or it could happen to
		 * be a transient write error and maybe the block will
		 * be remapped.  Nothing we can do but to retry the
		 * write and hope for the best.
		 */
		ext3_msg(sb, KERN_ERR, "previous I/O error to "
		       "superblock detected");
		clear_buffer_write_io_error(sbh);
		set_buffer_uptodate(sbh);
	}
	/*
	 * If the file system is mounted read-only, don't update the
	 * superblock write time.  This avoids updating the superblock
	 * write time when we are mounting the root file system
	 * read/only but we need to replay the journal; at that point,
	 * for people who are east of GMT and who make their clock
	 * tick in localtime for Windows bug-for-bug compatibility,
	 * the clock is set in the future, and this will cause e2fsck
	 * to complain and force a full file system check.
	 */
	if (!(sb->s_flags & MS_RDONLY))
		es->s_wtime = cpu_to_le32(get_seconds());
	es->s_free_blocks_count = cpu_to_le32(ext3_count_free_blocks(sb));
	es->s_free_inodes_count = cpu_to_le32(ext3_count_free_inodes(sb));
	BUFFER_TRACE(sbh, "marking dirty");
	mark_buffer_dirty(sbh);
	if (sync) {
		error = sync_dirty_buffer(sbh);
		if (buffer_write_io_error(sbh)) {
			ext3_msg(sb, KERN_ERR, "I/O error while writing "
			       "superblock");
			clear_buffer_write_io_error(sbh);
			set_buffer_uptodate(sbh);
		}
	}
	return error;
}