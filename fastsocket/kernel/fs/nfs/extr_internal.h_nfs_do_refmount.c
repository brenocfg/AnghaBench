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
struct vfsmount {int dummy; } ;
struct rpc_clnt {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 struct vfsmount* ERR_PTR (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline
struct vfsmount *nfs_do_refmount(struct rpc_clnt *client, const struct vfsmount *mnt_parent, struct dentry *dentry)
{
	return ERR_PTR(-ENOENT);
}