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
struct ocfs2_super {TYPE_2__* journal; } ;
struct inode {int i_state; int /*<<< orphan*/  i_sb; } ;
struct file {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; int /*<<< orphan*/  len; } ;
struct dentry {struct inode* d_inode; TYPE_1__ d_name; } ;
typedef  int /*<<< orphan*/  journal_t ;
struct TYPE_4__ {int /*<<< orphan*/ * j_journal; } ;

/* Variables and functions */
 int EIO ; 
 int I_DIRTY_DATASYNC ; 
 struct ocfs2_super* OCFS2_SB (int /*<<< orphan*/ ) ; 
 int jbd2_journal_force_commit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlog_entry (char*,struct file*,struct dentry*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_exit (int) ; 
 int ocfs2_sync_inode (struct inode*) ; 

__attribute__((used)) static int ocfs2_sync_file(struct file *file,
			   struct dentry *dentry,
			   int datasync)
{
	int err = 0;
	journal_t *journal;
	struct inode *inode = dentry->d_inode;
	struct ocfs2_super *osb = OCFS2_SB(inode->i_sb);

	mlog_entry("(0x%p, 0x%p, %d, '%.*s')\n", file, dentry, datasync,
		   dentry->d_name.len, dentry->d_name.name);

	err = ocfs2_sync_inode(dentry->d_inode);
	if (err)
		goto bail;

	if (datasync && !(inode->i_state & I_DIRTY_DATASYNC))
		goto bail;

	journal = osb->journal->j_journal;
	err = jbd2_journal_force_commit(journal);

bail:
	mlog_exit(err);

	return (err < 0) ? -EIO : 0;
}