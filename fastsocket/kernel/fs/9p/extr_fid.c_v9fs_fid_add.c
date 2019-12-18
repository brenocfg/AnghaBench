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
struct v9fs_dentry {int /*<<< orphan*/  lock; int /*<<< orphan*/  fidlist; } ;
struct p9_fid {int /*<<< orphan*/  dlist; int /*<<< orphan*/  fid; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct dentry {struct v9fs_dentry* d_fsdata; TYPE_1__ d_name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  P9_DEBUG_VFS ; 
 int /*<<< orphan*/  P9_DPRINTK (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct v9fs_dentry* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int v9fs_fid_add(struct dentry *dentry, struct p9_fid *fid)
{
	struct v9fs_dentry *dent;

	P9_DPRINTK(P9_DEBUG_VFS, "fid %d dentry %s\n",
					fid->fid, dentry->d_name.name);

	dent = dentry->d_fsdata;
	if (!dent) {
		dent = kmalloc(sizeof(struct v9fs_dentry), GFP_KERNEL);
		if (!dent)
			return -ENOMEM;

		spin_lock_init(&dent->lock);
		INIT_LIST_HEAD(&dent->fidlist);
		dentry->d_fsdata = dent;
	}

	spin_lock(&dent->lock);
	list_add(&fid->dlist, &dent->fidlist);
	spin_unlock(&dent->lock);

	return 0;
}