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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct v9fs_session_info {scalar_t__ cache; } ;
struct p9_fid {int /*<<< orphan*/  i_sb; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct TYPE_2__ {int name; } ;
struct dentry {int /*<<< orphan*/ * d_op; int /*<<< orphan*/  d_parent; TYPE_1__ d_name; } ;

/* Variables and functions */
 struct p9_fid* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct p9_fid*) ; 
 int /*<<< orphan*/  P9_DEBUG_VFS ; 
 int /*<<< orphan*/  P9_DPRINTK (int /*<<< orphan*/ ,char*,int) ; 
 int PTR_ERR (struct p9_fid*) ; 
 int /*<<< orphan*/  d_instantiate (struct dentry*,struct p9_fid*) ; 
 int /*<<< orphan*/  p9_client_clunk (struct p9_fid*) ; 
 int p9_client_fcreate (struct p9_fid*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 struct p9_fid* p9_client_walk (struct p9_fid*,int,char**,int) ; 
 int /*<<< orphan*/  v9fs_cached_dentry_operations ; 
 int /*<<< orphan*/  v9fs_dentry_operations ; 
 int v9fs_fid_add (struct dentry*,struct p9_fid*) ; 
 struct p9_fid* v9fs_fid_clone (int /*<<< orphan*/ ) ; 
 struct p9_fid* v9fs_inode_from_fid (struct v9fs_session_info*,struct p9_fid*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct p9_fid *
v9fs_create(struct v9fs_session_info *v9ses, struct inode *dir,
		struct dentry *dentry, char *extension, u32 perm, u8 mode)
{
	int err;
	char *name;
	struct p9_fid *dfid, *ofid, *fid;
	struct inode *inode;

	P9_DPRINTK(P9_DEBUG_VFS, "name %s\n", dentry->d_name.name);

	err = 0;
	ofid = NULL;
	fid = NULL;
	name = (char *) dentry->d_name.name;
	dfid = v9fs_fid_clone(dentry->d_parent);
	if (IS_ERR(dfid)) {
		err = PTR_ERR(dfid);
		P9_DPRINTK(P9_DEBUG_VFS, "fid clone failed %d\n", err);
		dfid = NULL;
		goto error;
	}

	/* clone a fid to use for creation */
	ofid = p9_client_walk(dfid, 0, NULL, 1);
	if (IS_ERR(ofid)) {
		err = PTR_ERR(ofid);
		P9_DPRINTK(P9_DEBUG_VFS, "p9_client_walk failed %d\n", err);
		ofid = NULL;
		goto error;
	}

	err = p9_client_fcreate(ofid, name, perm, mode, extension);
	if (err < 0) {
		P9_DPRINTK(P9_DEBUG_VFS, "p9_client_fcreate failed %d\n", err);
		goto error;
	}

	/* now walk from the parent so we can get unopened fid */
	fid = p9_client_walk(dfid, 1, &name, 0);
	if (IS_ERR(fid)) {
		err = PTR_ERR(fid);
		P9_DPRINTK(P9_DEBUG_VFS, "p9_client_walk failed %d\n", err);
		fid = NULL;
		goto error;
	} else
		dfid = NULL;

	/* instantiate inode and assign the unopened fid to the dentry */
	inode = v9fs_inode_from_fid(v9ses, fid, dir->i_sb);
	if (IS_ERR(inode)) {
		err = PTR_ERR(inode);
		P9_DPRINTK(P9_DEBUG_VFS, "inode creation failed %d\n", err);
		goto error;
	}

	if (v9ses->cache)
		dentry->d_op = &v9fs_cached_dentry_operations;
	else
		dentry->d_op = &v9fs_dentry_operations;

	d_instantiate(dentry, inode);
	err = v9fs_fid_add(dentry, fid);
	if (err < 0)
		goto error;

	return ofid;

error:
	if (dfid)
		p9_client_clunk(dfid);

	if (ofid)
		p9_client_clunk(ofid);

	if (fid)
		p9_client_clunk(fid);

	return ERR_PTR(err);
}