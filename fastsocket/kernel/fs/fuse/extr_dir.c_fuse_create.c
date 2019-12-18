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
struct nameidata {int flags; } ;
struct inode {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int ENOSYS ; 
 int LOOKUP_OPEN ; 
 int fuse_create_open (struct inode*,struct dentry*,int,struct nameidata*) ; 
 int fuse_mknod (struct inode*,struct dentry*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fuse_create(struct inode *dir, struct dentry *entry, int mode,
		       struct nameidata *nd)
{
	if (nd && (nd->flags & LOOKUP_OPEN)) {
		int err = fuse_create_open(dir, entry, mode, nd);
		if (err != -ENOSYS)
			return err;
		/* Fall back on mknod */
	}
	return fuse_mknod(dir, entry, mode, 0);
}