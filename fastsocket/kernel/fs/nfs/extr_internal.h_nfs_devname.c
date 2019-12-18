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
struct vfsmount {int /*<<< orphan*/  mnt_root; int /*<<< orphan*/  mnt_devname; } ;
struct dentry {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 char* nfs_path (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dentry const*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline char *nfs_devname(const struct vfsmount *mnt_parent,
				const struct dentry *dentry,
				char *buffer, ssize_t buflen)
{
	return nfs_path(mnt_parent->mnt_devname, mnt_parent->mnt_root,
			dentry, buffer, buflen);
}