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
struct pipe_inode_info {int readers; int writers; } ;
struct inode {int i_mode; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_atime; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; int /*<<< orphan*/  i_state; int /*<<< orphan*/ * i_fop; struct pipe_inode_info* i_pipe; } ;
struct TYPE_2__ {int /*<<< orphan*/  mnt_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURRENT_TIME ; 
 int /*<<< orphan*/  I_DIRTY ; 
 int S_IFIFO ; 
 int S_IRUSR ; 
 int S_IWUSR ; 
 struct pipe_inode_info* alloc_pipe_info (struct inode*) ; 
 int /*<<< orphan*/  current_fsgid () ; 
 int /*<<< orphan*/  current_fsuid () ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 struct inode* new_inode (int /*<<< orphan*/ ) ; 
 TYPE_1__* pipe_mnt ; 
 int /*<<< orphan*/  rdwr_pipefifo_fops ; 

__attribute__((used)) static struct inode * get_pipe_inode(void)
{
	struct inode *inode = new_inode(pipe_mnt->mnt_sb);
	struct pipe_inode_info *pipe;

	if (!inode)
		goto fail_inode;

	pipe = alloc_pipe_info(inode);
	if (!pipe)
		goto fail_iput;
	inode->i_pipe = pipe;

	pipe->readers = pipe->writers = 1;
	inode->i_fop = &rdwr_pipefifo_fops;

	/*
	 * Mark the inode dirty from the very beginning,
	 * that way it will never be moved to the dirty
	 * list because "mark_inode_dirty()" will think
	 * that it already _is_ on the dirty list.
	 */
	inode->i_state = I_DIRTY;
	inode->i_mode = S_IFIFO | S_IRUSR | S_IWUSR;
	inode->i_uid = current_fsuid();
	inode->i_gid = current_fsgid();
	inode->i_atime = inode->i_mtime = inode->i_ctime = CURRENT_TIME;

	return inode;

fail_iput:
	iput(inode);

fail_inode:
	return NULL;
}