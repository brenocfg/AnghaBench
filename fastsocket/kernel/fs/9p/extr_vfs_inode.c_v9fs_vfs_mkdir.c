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
typedef  int /*<<< orphan*/  u32 ;
struct v9fs_session_info {int dummy; } ;
struct p9_fid {int dummy; } ;
struct inode {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct dentry {TYPE_1__ d_name; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct p9_fid*) ; 
 int /*<<< orphan*/  P9_DEBUG_VFS ; 
 int /*<<< orphan*/  P9_DPRINTK (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  P9_OREAD ; 
 int PTR_ERR (struct p9_fid*) ; 
 int S_IFDIR ; 
 int /*<<< orphan*/  p9_client_clunk (struct p9_fid*) ; 
 int /*<<< orphan*/  unixmode2p9mode (struct v9fs_session_info*,int) ; 
 struct p9_fid* v9fs_create (struct v9fs_session_info*,struct inode*,struct dentry*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct v9fs_session_info* v9fs_inode2v9ses (struct inode*) ; 

__attribute__((used)) static int v9fs_vfs_mkdir(struct inode *dir, struct dentry *dentry, int mode)
{
	int err;
	u32 perm;
	struct v9fs_session_info *v9ses;
	struct p9_fid *fid;

	P9_DPRINTK(P9_DEBUG_VFS, "name %s\n", dentry->d_name.name);
	err = 0;
	v9ses = v9fs_inode2v9ses(dir);
	perm = unixmode2p9mode(v9ses, mode | S_IFDIR);
	fid = v9fs_create(v9ses, dir, dentry, NULL, perm, P9_OREAD);
	if (IS_ERR(fid)) {
		err = PTR_ERR(fid);
		fid = NULL;
	}

	if (fid)
		p9_client_clunk(fid);

	return err;
}