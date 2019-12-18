#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct v9fs_session_info {scalar_t__ cache; } ;
struct super_block {int dummy; } ;
struct TYPE_4__ {scalar_t__ version; } ;
struct p9_fid {TYPE_2__ qid; struct super_block* i_sb; } ;
struct nameidata {int dummy; } ;
struct inode {TYPE_2__ qid; struct super_block* i_sb; } ;
struct TYPE_3__ {scalar_t__ name; } ;
struct dentry {int /*<<< orphan*/ * d_op; TYPE_1__ d_name; int /*<<< orphan*/  d_parent; } ;

/* Variables and functions */
 int ENOENT ; 
 struct dentry* ERR_CAST (struct p9_fid*) ; 
 struct dentry* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct p9_fid*) ; 
 int /*<<< orphan*/  P9_DEBUG_VFS ; 
 int /*<<< orphan*/  P9_DPRINTK (int /*<<< orphan*/ ,char*,struct p9_fid*,scalar_t__,struct dentry*,struct nameidata*) ; 
 int PTR_ERR (struct p9_fid*) ; 
 int /*<<< orphan*/  d_add (struct dentry*,struct p9_fid*) ; 
 int /*<<< orphan*/  p9_client_clunk (struct p9_fid*) ; 
 struct p9_fid* p9_client_walk (struct p9_fid*,int,char**,int) ; 
 int /*<<< orphan*/  v9fs_cached_dentry_operations ; 
 int /*<<< orphan*/  v9fs_dentry_operations ; 
 int v9fs_fid_add (struct dentry*,struct p9_fid*) ; 
 struct p9_fid* v9fs_fid_lookup (int /*<<< orphan*/ ) ; 
 struct v9fs_session_info* v9fs_inode2v9ses (struct p9_fid*) ; 
 struct p9_fid* v9fs_inode_from_fid (struct v9fs_session_info*,struct p9_fid*,struct super_block*) ; 

__attribute__((used)) static struct dentry *v9fs_vfs_lookup(struct inode *dir, struct dentry *dentry,
				      struct nameidata *nameidata)
{
	struct super_block *sb;
	struct v9fs_session_info *v9ses;
	struct p9_fid *dfid, *fid;
	struct inode *inode;
	char *name;
	int result = 0;

	P9_DPRINTK(P9_DEBUG_VFS, "dir: %p dentry: (%s) %p nameidata: %p\n",
		dir, dentry->d_name.name, dentry, nameidata);

	sb = dir->i_sb;
	v9ses = v9fs_inode2v9ses(dir);
	dfid = v9fs_fid_lookup(dentry->d_parent);
	if (IS_ERR(dfid))
		return ERR_CAST(dfid);

	name = (char *) dentry->d_name.name;
	fid = p9_client_walk(dfid, 1, &name, 1);
	if (IS_ERR(fid)) {
		result = PTR_ERR(fid);
		if (result == -ENOENT) {
			d_add(dentry, NULL);
			return NULL;
		}

		return ERR_PTR(result);
	}

	inode = v9fs_inode_from_fid(v9ses, fid, dir->i_sb);
	if (IS_ERR(inode)) {
		result = PTR_ERR(inode);
		inode = NULL;
		goto error;
	}

	result = v9fs_fid_add(dentry, fid);
	if (result < 0)
		goto error;

	if ((fid->qid.version) && (v9ses->cache))
		dentry->d_op = &v9fs_cached_dentry_operations;
	else
		dentry->d_op = &v9fs_dentry_operations;

	d_add(dentry, inode);
	return NULL;

error:
	p9_client_clunk(fid);

	return ERR_PTR(result);
}