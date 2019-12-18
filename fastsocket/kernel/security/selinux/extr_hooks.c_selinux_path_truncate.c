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
typedef  scalar_t__ u32 ;
struct path {TYPE_1__* dentry; } ;
struct inode {int dummy; } ;
struct cred {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_2__ {struct inode* d_inode; } ;

/* Variables and functions */
 struct cred* current_cred () ; 
 int inode_has_perm (struct cred const*,struct inode*,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ open_inode_to_av (struct inode*) ; 

__attribute__((used)) static int selinux_path_truncate(struct path *path, loff_t length,
				 unsigned int time_attrs)
{
	const struct cred *cred = current_cred();
	struct inode *inode = path->dentry->d_inode;
	u32 av = open_inode_to_av(inode);

	if (av)
		return inode_has_perm(cred, inode, av, NULL);

	return 0;
}