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
typedef  scalar_t__ u32 ;
struct inode_security_struct {scalar_t__ sid; } ;
struct inode {struct inode_security_struct* i_security; } ;
struct file_security_struct {scalar_t__ sid; scalar_t__ isid; scalar_t__ pseqno; } ;
struct TYPE_4__ {TYPE_1__* dentry; } ;
struct file {struct file_security_struct* f_security; TYPE_2__ f_path; } ;
struct TYPE_3__ {struct inode* d_inode; } ;

/* Variables and functions */
 scalar_t__ avc_policy_seqno () ; 
 scalar_t__ current_sid () ; 
 int selinux_revalidate_file_permission (struct file*,int) ; 

__attribute__((used)) static int selinux_file_permission(struct file *file, int mask)
{
	struct inode *inode = file->f_path.dentry->d_inode;
	struct file_security_struct *fsec = file->f_security;
	struct inode_security_struct *isec = inode->i_security;
	u32 sid = current_sid();

	if (!mask)
		/* No permission to check.  Existence test. */
		return 0;

	if (sid == fsec->sid && fsec->isid == isec->sid &&
	    fsec->pseqno == avc_policy_seqno())
		/* No change since dentry_open check. */
		return 0;

	return selinux_revalidate_file_permission(file, mask);
}