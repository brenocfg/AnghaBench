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
struct v9fs_session_info {int dummy; } ;
struct p9_fid {int dummy; } ;
struct inode {int dummy; } ;
struct dentry {struct inode* d_inode; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct p9_fid*) ; 
 int /*<<< orphan*/  P9_DEBUG_VFS ; 
 int /*<<< orphan*/  P9_DPRINTK (int /*<<< orphan*/ ,char*,struct inode*,struct dentry*,int) ; 
 int PTR_ERR (struct p9_fid*) ; 
 int p9_client_remove (struct p9_fid*) ; 
 struct p9_fid* v9fs_fid_clone (struct dentry*) ; 
 struct v9fs_session_info* v9fs_inode2v9ses (struct inode*) ; 

__attribute__((used)) static int v9fs_remove(struct inode *dir, struct dentry *file, int rmdir)
{
	struct inode *file_inode;
	struct v9fs_session_info *v9ses;
	struct p9_fid *v9fid;

	P9_DPRINTK(P9_DEBUG_VFS, "inode: %p dentry: %p rmdir: %d\n", dir, file,
		rmdir);

	file_inode = file->d_inode;
	v9ses = v9fs_inode2v9ses(file_inode);
	v9fid = v9fs_fid_clone(file);
	if (IS_ERR(v9fid))
		return PTR_ERR(v9fid);

	return p9_client_remove(v9fid);
}