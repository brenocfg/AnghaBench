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
struct inode {int /*<<< orphan*/  i_sb; scalar_t__ i_blocks; scalar_t__ i_size; int /*<<< orphan*/  i_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_dtime; } ;

/* Variables and functions */
 TYPE_1__* EXT2_I (struct inode*) ; 
 int /*<<< orphan*/  __ext2_write_inode (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_inode (struct inode*) ; 
 int /*<<< orphan*/  ext2_free_inode (struct inode*) ; 
 int /*<<< orphan*/  ext2_truncate (struct inode*) ; 
 int /*<<< orphan*/  get_seconds () ; 
 int /*<<< orphan*/  inode_needs_sync (struct inode*) ; 
 scalar_t__ is_bad_inode (struct inode*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int /*<<< orphan*/  sb_end_intwrite (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sb_start_intwrite (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  truncate_inode_pages (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void ext2_delete_inode (struct inode * inode)
{
	truncate_inode_pages(&inode->i_data, 0);

	if (is_bad_inode(inode))
		goto no_delete;
	sb_start_intwrite(inode->i_sb);
	EXT2_I(inode)->i_dtime	= get_seconds();
	mark_inode_dirty(inode);
	__ext2_write_inode(inode, inode_needs_sync(inode));

	inode->i_size = 0;
	if (inode->i_blocks)
		ext2_truncate (inode);
	ext2_free_inode (inode);
	sb_end_intwrite(inode->i_sb);

	return;
no_delete:
	clear_inode(inode);	/* We must guarantee clearing of inode... */
}