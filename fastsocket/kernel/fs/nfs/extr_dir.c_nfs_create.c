#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int flags; } ;
struct TYPE_9__ {TYPE_3__ open; } ;
struct nameidata {int flags; TYPE_4__ intent; } ;
struct inode {int /*<<< orphan*/  i_ino; TYPE_1__* i_sb; } ;
struct iattr {int ia_mode; int /*<<< orphan*/  ia_valid; } ;
struct TYPE_7__ {int /*<<< orphan*/  name; } ;
struct dentry {TYPE_2__ d_name; } ;
struct TYPE_10__ {int (* create ) (struct inode*,struct dentry*,struct iattr*,int,int /*<<< orphan*/ *) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  s_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_MODE ; 
 int LOOKUP_CREATE ; 
 TYPE_5__* NFS_PROTO (struct inode*) ; 
 int /*<<< orphan*/  VFS ; 
 int /*<<< orphan*/  d_drop (struct dentry*) ; 
 int /*<<< orphan*/  dfprintk (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (struct inode*,struct dentry*,struct iattr*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nfs_create(struct inode *dir, struct dentry *dentry, int mode,
		struct nameidata *nd)
{
	struct iattr attr;
	int error;
	int open_flags = 0;

	dfprintk(VFS, "NFS: create(%s/%ld), %s\n",
			dir->i_sb->s_id, dir->i_ino, dentry->d_name.name);

	attr.ia_mode = mode;
	attr.ia_valid = ATTR_MODE;

	if ((nd->flags & LOOKUP_CREATE) != 0)
		open_flags = nd->intent.open.flags;

	error = NFS_PROTO(dir)->create(dir, dentry, &attr, open_flags, NULL);
	if (error != 0)
		goto out_err;
	return 0;
out_err:
	d_drop(dentry);
	return error;
}