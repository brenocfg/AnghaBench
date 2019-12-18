#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct vfsmount {int dummy; } ;
struct inode {int dummy; } ;
struct dentry {struct inode* d_inode; } ;
struct cred {int dummy; } ;
struct TYPE_4__ {struct dentry* dentry; struct vfsmount* mnt; } ;
struct TYPE_5__ {TYPE_1__ path; } ;
struct TYPE_6__ {TYPE_2__ fs; } ;
struct common_audit_data {TYPE_3__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMMON_AUDIT_DATA_INIT (struct common_audit_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FS ; 
 int inode_has_perm (struct cred const*,struct inode*,int /*<<< orphan*/ ,struct common_audit_data*) ; 

__attribute__((used)) static inline int dentry_has_perm(const struct cred *cred,
				  struct vfsmount *mnt,
				  struct dentry *dentry,
				  u32 av)
{
	struct inode *inode = dentry->d_inode;
	struct common_audit_data ad;

	COMMON_AUDIT_DATA_INIT(&ad, FS);
	ad.u.fs.path.mnt = mnt;
	ad.u.fs.path.dentry = dentry;
	return inode_has_perm(cred, inode, av, &ad);
}