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
struct v9fs_session_info {int /*<<< orphan*/  uname; } ;
struct p9_wstat {char* name; int /*<<< orphan*/  muid; } ;
struct p9_fid {int /*<<< orphan*/  qid; } ;
struct inode {int dummy; } ;
struct TYPE_2__ {scalar_t__ name; } ;
struct dentry {TYPE_1__ d_name; int /*<<< orphan*/  d_parent; struct inode* d_inode; } ;

/* Variables and functions */
 int EXDEV ; 
 scalar_t__ IS_ERR (struct p9_fid*) ; 
 int /*<<< orphan*/  P9_DEBUG_ERROR ; 
 int /*<<< orphan*/  P9_DEBUG_VFS ; 
 int /*<<< orphan*/  P9_DPRINTK (int /*<<< orphan*/ ,char*) ; 
 int PTR_ERR (struct p9_fid*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  p9_client_clunk (struct p9_fid*) ; 
 int p9_client_wstat (struct p9_fid*,struct p9_wstat*) ; 
 int /*<<< orphan*/  v9fs_blank_wstat (struct p9_wstat*) ; 
 struct p9_fid* v9fs_fid_clone (int /*<<< orphan*/ ) ; 
 struct p9_fid* v9fs_fid_lookup (struct dentry*) ; 
 struct v9fs_session_info* v9fs_inode2v9ses (struct inode*) ; 

__attribute__((used)) static int
v9fs_vfs_rename(struct inode *old_dir, struct dentry *old_dentry,
		struct inode *new_dir, struct dentry *new_dentry)
{
	struct inode *old_inode;
	struct v9fs_session_info *v9ses;
	struct p9_fid *oldfid;
	struct p9_fid *olddirfid;
	struct p9_fid *newdirfid;
	struct p9_wstat wstat;
	int retval;

	P9_DPRINTK(P9_DEBUG_VFS, "\n");
	retval = 0;
	old_inode = old_dentry->d_inode;
	v9ses = v9fs_inode2v9ses(old_inode);
	oldfid = v9fs_fid_lookup(old_dentry);
	if (IS_ERR(oldfid))
		return PTR_ERR(oldfid);

	olddirfid = v9fs_fid_clone(old_dentry->d_parent);
	if (IS_ERR(olddirfid)) {
		retval = PTR_ERR(olddirfid);
		goto done;
	}

	newdirfid = v9fs_fid_clone(new_dentry->d_parent);
	if (IS_ERR(newdirfid)) {
		retval = PTR_ERR(newdirfid);
		goto clunk_olddir;
	}

	/* 9P can only handle file rename in the same directory */
	if (memcmp(&olddirfid->qid, &newdirfid->qid, sizeof(newdirfid->qid))) {
		P9_DPRINTK(P9_DEBUG_ERROR,
				"old dir and new dir are different\n");
		retval = -EXDEV;
		goto clunk_newdir;
	}

	v9fs_blank_wstat(&wstat);
	wstat.muid = v9ses->uname;
	wstat.name = (char *) new_dentry->d_name.name;
	retval = p9_client_wstat(oldfid, &wstat);

clunk_newdir:
	p9_client_clunk(newdirfid);

clunk_olddir:
	p9_client_clunk(olddirfid);

done:
	return retval;
}