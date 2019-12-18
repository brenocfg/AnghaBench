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
typedef  int /*<<< orphan*/  u32 ;
struct v9fs_session_info {int dummy; } ;
struct p9_fid {int dummy; } ;
struct inode {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int EPERM ; 
 scalar_t__ IS_ERR (struct p9_fid*) ; 
 int /*<<< orphan*/  P9_DEBUG_ERROR ; 
 int /*<<< orphan*/  P9_DPRINTK (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  P9_OREAD ; 
 int PTR_ERR (struct p9_fid*) ; 
 int /*<<< orphan*/  p9_client_clunk (struct p9_fid*) ; 
 int /*<<< orphan*/  unixmode2p9mode (struct v9fs_session_info*,int) ; 
 struct p9_fid* v9fs_create (struct v9fs_session_info*,struct inode*,struct dentry*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v9fs_extended (struct v9fs_session_info*) ; 
 struct v9fs_session_info* v9fs_inode2v9ses (struct inode*) ; 

__attribute__((used)) static int v9fs_vfs_mkspecial(struct inode *dir, struct dentry *dentry,
	int mode, const char *extension)
{
	u32 perm;
	struct v9fs_session_info *v9ses;
	struct p9_fid *fid;

	v9ses = v9fs_inode2v9ses(dir);
	if (!v9fs_extended(v9ses)) {
		P9_DPRINTK(P9_DEBUG_ERROR, "not extended\n");
		return -EPERM;
	}

	perm = unixmode2p9mode(v9ses, mode);
	fid = v9fs_create(v9ses, dir, dentry, (char *) extension, perm,
								P9_OREAD);
	if (IS_ERR(fid))
		return PTR_ERR(fid);

	p9_client_clunk(fid);
	return 0;
}