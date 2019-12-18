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
struct p9_fid {int fid; } ;
struct inode {int /*<<< orphan*/  i_ino; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct dentry {TYPE_1__ d_name; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct p9_fid*) ; 
 int /*<<< orphan*/  P9_DEBUG_VFS ; 
 int /*<<< orphan*/  P9_DMLINK ; 
 int /*<<< orphan*/  P9_DPRINTK (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PTR_ERR (struct p9_fid*) ; 
 char* __getname () ; 
 int /*<<< orphan*/  __putname (char*) ; 
 int /*<<< orphan*/  p9_client_clunk (struct p9_fid*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 scalar_t__ unlikely (int) ; 
 struct p9_fid* v9fs_fid_clone (struct dentry*) ; 
 int v9fs_vfs_mkspecial (struct inode*,struct dentry*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
v9fs_vfs_link(struct dentry *old_dentry, struct inode *dir,
	      struct dentry *dentry)
{
	int retval;
	struct p9_fid *oldfid;
	char *name;

	P9_DPRINTK(P9_DEBUG_VFS,
		" %lu,%s,%s\n", dir->i_ino, dentry->d_name.name,
		old_dentry->d_name.name);

	oldfid = v9fs_fid_clone(old_dentry);
	if (IS_ERR(oldfid))
		return PTR_ERR(oldfid);

	name = __getname();
	if (unlikely(!name)) {
		retval = -ENOMEM;
		goto clunk_fid;
	}

	sprintf(name, "%d\n", oldfid->fid);
	retval = v9fs_vfs_mkspecial(dir, dentry, P9_DMLINK, name);
	__putname(name);

clunk_fid:
	p9_client_clunk(oldfid);
	return retval;
}