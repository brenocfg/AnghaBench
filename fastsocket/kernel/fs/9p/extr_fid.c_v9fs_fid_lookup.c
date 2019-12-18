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
struct v9fs_session_info {int flags; char* uname; int /*<<< orphan*/  aname; int /*<<< orphan*/  clnt; int /*<<< orphan*/  uid; } ;
struct p9_fid {int dummy; } ;
struct TYPE_2__ {scalar_t__ name; } ;
struct dentry {TYPE_1__ d_name; struct dentry* d_parent; int /*<<< orphan*/  d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  EPERM ; 
 struct p9_fid* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct p9_fid*) ; 
 int /*<<< orphan*/  IS_ROOT (struct dentry*) ; 
 int /*<<< orphan*/  P9_MAXWELEM ; 
#define  V9FS_ACCESS_ANY 130 
 int V9FS_ACCESS_MASK ; 
#define  V9FS_ACCESS_SINGLE 129 
#define  V9FS_ACCESS_USER 128 
 int /*<<< orphan*/  current_fsuid () ; 
 int /*<<< orphan*/  kfree (char**) ; 
 char** kmalloc (int,int /*<<< orphan*/ ) ; 
 int min (int,int /*<<< orphan*/ ) ; 
 struct p9_fid* p9_client_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct p9_fid* p9_client_walk (struct p9_fid*,int,char**,int) ; 
 scalar_t__ v9fs_extended (struct v9fs_session_info*) ; 
 int /*<<< orphan*/  v9fs_fid_add (struct dentry*,struct p9_fid*) ; 
 struct p9_fid* v9fs_fid_find (struct dentry*,int /*<<< orphan*/ ,int) ; 
 struct v9fs_session_info* v9fs_inode2v9ses (int /*<<< orphan*/ ) ; 

struct p9_fid *v9fs_fid_lookup(struct dentry *dentry)
{
	int i, n, l, clone, any, access;
	u32 uid;
	struct p9_fid *fid;
	struct dentry *d, *ds;
	struct v9fs_session_info *v9ses;
	char **wnames, *uname;

	v9ses = v9fs_inode2v9ses(dentry->d_inode);
	access = v9ses->flags & V9FS_ACCESS_MASK;
	switch (access) {
	case V9FS_ACCESS_SINGLE:
	case V9FS_ACCESS_USER:
		uid = current_fsuid();
		any = 0;
		break;

	case V9FS_ACCESS_ANY:
		uid = v9ses->uid;
		any = 1;
		break;

	default:
		uid = ~0;
		any = 0;
		break;
	}

	fid = v9fs_fid_find(dentry, uid, any);
	if (fid)
		return fid;

	ds = dentry->d_parent;
	fid = v9fs_fid_find(ds, uid, any);
	if (!fid) { /* walk from the root */
		n = 0;
		for (ds = dentry; !IS_ROOT(ds); ds = ds->d_parent)
			n++;

		fid = v9fs_fid_find(ds, uid, any);
		if (!fid) { /* the user is not attached to the fs yet */
			if (access == V9FS_ACCESS_SINGLE)
				return ERR_PTR(-EPERM);

			if (v9fs_extended(v9ses))
				uname = NULL;
			else
				uname = v9ses->uname;

			fid = p9_client_attach(v9ses->clnt, NULL, uname, uid,
				v9ses->aname);

			if (IS_ERR(fid))
				return fid;

			v9fs_fid_add(ds, fid);
		}
	} else /* walk from the parent */
		n = 1;

	if (ds == dentry)
		return fid;

	wnames = kmalloc(sizeof(char *) * n, GFP_KERNEL);
	if (!wnames)
		return ERR_PTR(-ENOMEM);

	for (d = dentry, i = (n-1); i >= 0; i--, d = d->d_parent)
		wnames[i] = (char *) d->d_name.name;

	clone = 1;
	i = 0;
	while (i < n) {
		l = min(n - i, P9_MAXWELEM);
		fid = p9_client_walk(fid, l, &wnames[i], clone);
		if (IS_ERR(fid)) {
			kfree(wnames);
			return fid;
		}

		i += l;
		clone = 0;
	}

	kfree(wnames);
	v9fs_fid_add(dentry, fid);
	return fid;
}