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
struct ocfs2_super {int dummy; } ;
struct ocfs2_space_resv {int dummy; } ;
struct inode {int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_sb; } ;
struct TYPE_4__ {TYPE_1__* dentry; } ;
struct file {int f_mode; int /*<<< orphan*/  f_pos; TYPE_2__ f_path; } ;
struct TYPE_3__ {struct inode* d_inode; } ;

/* Variables and functions */
 int EBADF ; 
 int EINVAL ; 
 int ENOTTY ; 
 int FMODE_WRITE ; 
 unsigned int OCFS2_IOC_RESVSP ; 
 unsigned int OCFS2_IOC_RESVSP64 ; 
 unsigned int OCFS2_IOC_UNRESVSP ; 
 unsigned int OCFS2_IOC_UNRESVSP64 ; 
 struct ocfs2_super* OCFS2_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int __ocfs2_change_file_space (struct file*,struct inode*,int /*<<< orphan*/ ,unsigned int,struct ocfs2_space_resv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_sparse_alloc (struct ocfs2_super*) ; 
 int /*<<< orphan*/  ocfs2_writes_unwritten_extents (struct ocfs2_super*) ; 

int ocfs2_change_file_space(struct file *file, unsigned int cmd,
			    struct ocfs2_space_resv *sr)
{
	struct inode *inode = file->f_path.dentry->d_inode;
	struct ocfs2_super *osb = OCFS2_SB(inode->i_sb);

	if ((cmd == OCFS2_IOC_RESVSP || cmd == OCFS2_IOC_RESVSP64) &&
	    !ocfs2_writes_unwritten_extents(osb))
		return -ENOTTY;
	else if ((cmd == OCFS2_IOC_UNRESVSP || cmd == OCFS2_IOC_UNRESVSP64) &&
		 !ocfs2_sparse_alloc(osb))
		return -ENOTTY;

	if (!S_ISREG(inode->i_mode))
		return -EINVAL;

	if (!(file->f_mode & FMODE_WRITE))
		return -EBADF;

	return __ocfs2_change_file_space(file, inode, file->f_pos, cmd, sr, 0);
}