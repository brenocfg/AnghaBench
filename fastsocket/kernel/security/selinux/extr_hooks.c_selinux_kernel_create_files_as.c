#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct task_security_struct {int /*<<< orphan*/  create_sid; } ;
struct inode_security_struct {int /*<<< orphan*/  sid; } ;
struct inode {struct inode_security_struct* i_security; } ;
struct cred {struct task_security_struct* security; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERNEL_SERVICE__CREATE_FILES_AS ; 
 int /*<<< orphan*/  SECCLASS_KERNEL_SERVICE ; 
 int avc_has_perm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current_sid () ; 

__attribute__((used)) static int selinux_kernel_create_files_as(struct cred *new, struct inode *inode)
{
	struct inode_security_struct *isec = inode->i_security;
	struct task_security_struct *tsec = new->security;
	u32 sid = current_sid();
	int ret;

	ret = avc_has_perm(sid, isec->sid,
			   SECCLASS_KERNEL_SERVICE,
			   KERNEL_SERVICE__CREATE_FILES_AS,
			   NULL);

	if (ret == 0)
		tsec->create_sid = isec->sid;
	return ret;
}