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
struct TYPE_5__ {int /*<<< orphan*/ * mnt; } ;
struct TYPE_4__ {TYPE_3__* dentry; } ;
struct nameidata {TYPE_2__ root; TYPE_1__ path; } ;
struct filename {int /*<<< orphan*/  name; } ;
struct TYPE_6__ {scalar_t__ d_inode; } ;

/* Variables and functions */
 unsigned int LOOKUP_PARENT ; 
 int /*<<< orphan*/  audit_dummy_context () ; 
 int /*<<< orphan*/  audit_inode (struct filename*,TYPE_3__*,unsigned int) ; 
 int path_init (int,int /*<<< orphan*/ ,unsigned int,struct nameidata*) ; 
 int /*<<< orphan*/  path_put (TYPE_2__*) ; 
 int path_walk (struct filename*,struct nameidata*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int filename_lookup(int dfd, struct filename *filename,
				unsigned int flags, struct nameidata *nd)
{
	int retval = path_init(dfd, filename->name, flags, nd);
	if (!retval)
		retval = path_walk(filename, nd);
	if (unlikely(!retval && !audit_dummy_context() && nd->path.dentry &&
				nd->path.dentry->d_inode))
		audit_inode(filename, nd->path.dentry, flags & LOOKUP_PARENT);
	if (nd->root.mnt) {
		path_put(&nd->root);
		nd->root.mnt = NULL;
	}
	return retval;
}