#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vfsmount {int dummy; } ;
struct TYPE_3__ {struct vfsmount* mnt; struct dentry* dentry; } ;
struct nameidata {unsigned int flags; TYPE_1__ root; TYPE_1__ path; scalar_t__ depth; int /*<<< orphan*/  last_type; } ;
struct filename {char const* name; } ;
struct dentry {scalar_t__ d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  LAST_ROOT ; 
 unsigned int LOOKUP_PARENT ; 
 int /*<<< orphan*/  audit_dummy_context () ; 
 int /*<<< orphan*/  audit_inode (struct filename*,struct dentry*,unsigned int) ; 
 int /*<<< orphan*/  path_get (TYPE_1__*) ; 
 int /*<<< orphan*/  path_put (TYPE_1__*) ; 
 int path_walk (struct filename*,struct nameidata*) ; 
 scalar_t__ unlikely (int) ; 

int vfs_path_lookup(struct dentry *dentry, struct vfsmount *mnt,
		    const char *name, unsigned int flags,
		    struct nameidata *nd)
{
	int retval;
	struct filename filename = { .name = name };

	/* same as do_path_lookup */
	nd->last_type = LAST_ROOT;
	nd->flags = flags;
	nd->depth = 0;

	nd->path.dentry = dentry;
	nd->path.mnt = mnt;
	path_get(&nd->path);
	nd->root = nd->path;
	path_get(&nd->root);

	retval = path_walk(&filename, nd);
	if (unlikely(!retval && !audit_dummy_context() && nd->path.dentry &&
				nd->path.dentry->d_inode))
		audit_inode(&filename, nd->path.dentry, flags & LOOKUP_PARENT);

	path_put(&nd->root);
	nd->root.mnt = NULL;

	return retval;
}