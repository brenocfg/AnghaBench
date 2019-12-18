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
struct inode_security_struct {int /*<<< orphan*/  sid; } ;
struct inode {struct inode_security_struct* i_security; } ;
struct file_security_struct {int /*<<< orphan*/  pseqno; int /*<<< orphan*/  isid; } ;
struct TYPE_4__ {TYPE_1__* dentry; } ;
struct file {struct file_security_struct* f_security; TYPE_2__ f_path; } ;
struct cred {int dummy; } ;
struct TYPE_3__ {struct inode* d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  avc_policy_seqno () ; 
 int inode_has_perm (struct cred const*,struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  open_file_to_av (struct file*) ; 

__attribute__((used)) static int selinux_dentry_open(struct file *file, const struct cred *cred)
{
	struct file_security_struct *fsec;
	struct inode *inode;
	struct inode_security_struct *isec;

	inode = file->f_path.dentry->d_inode;
	fsec = file->f_security;
	isec = inode->i_security;
	/*
	 * Save inode label and policy sequence number
	 * at open-time so that selinux_file_permission
	 * can determine whether revalidation is necessary.
	 * Task label is already saved in the file security
	 * struct as its SID.
	 */
	fsec->isid = isec->sid;
	fsec->pseqno = avc_policy_seqno();
	/*
	 * Since the inode label or policy seqno may have changed
	 * between the selinux_inode_permission check and the saving
	 * of state above, recheck that access is still permitted.
	 * Otherwise, access might never be revalidated against the
	 * new inode label or new policy.
	 * This check is not redundant - do not remove.
	 */
	return inode_has_perm(cred, inode, open_file_to_av(file), NULL);
}