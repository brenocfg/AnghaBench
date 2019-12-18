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
struct ocfs2_super {int s_mount_opt; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct file_lock {int fl_flags; scalar_t__ fl_type; } ;
struct file {TYPE_1__* f_mapping; } ;
struct TYPE_2__ {struct inode* host; } ;

/* Variables and functions */
 int ENOLCK ; 
 int FL_FLOCK ; 
 scalar_t__ F_UNLCK ; 
 int OCFS2_MOUNT_LOCALFLOCKS ; 
 struct ocfs2_super* OCFS2_SB (int /*<<< orphan*/ ) ; 
 scalar_t__ __mandatory_lock (struct inode*) ; 
 int flock_lock_file_wait (struct file*,struct file_lock*) ; 
 int ocfs2_do_flock (struct file*,struct inode*,int,struct file_lock*) ; 
 int ocfs2_do_funlock (struct file*,int,struct file_lock*) ; 
 scalar_t__ ocfs2_mount_local (struct ocfs2_super*) ; 

int ocfs2_flock(struct file *file, int cmd, struct file_lock *fl)
{
	struct inode *inode = file->f_mapping->host;
	struct ocfs2_super *osb = OCFS2_SB(inode->i_sb);

	if (!(fl->fl_flags & FL_FLOCK))
		return -ENOLCK;
	if (__mandatory_lock(inode))
		return -ENOLCK;

	if ((osb->s_mount_opt & OCFS2_MOUNT_LOCALFLOCKS) ||
	    ocfs2_mount_local(osb))
		return flock_lock_file_wait(file, fl);

	if (fl->fl_type == F_UNLCK)
		return ocfs2_do_funlock(file, cmd, fl);
	else
		return ocfs2_do_flock(file, inode, cmd, fl);
}