#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vfsmount {int dummy; } ;
struct qstr {char* name; size_t len; } ;
struct path {struct dentry* dentry; struct vfsmount* mnt; } ;
struct TYPE_5__ {struct dentry* dentry; struct vfsmount* mnt; } ;
struct nameidata {int flags; TYPE_2__ path; } ;
struct inode {int /*<<< orphan*/  i_mutex; TYPE_3__* i_op; } ;
struct dentry {struct inode* d_inode; TYPE_1__* d_op; } ;
struct TYPE_6__ {struct dentry* (* lookup ) (struct inode*,struct dentry*,struct nameidata*) ;} ;
struct TYPE_4__ {scalar_t__ d_revalidate; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct dentry* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_DEADDIR (struct inode*) ; 
 scalar_t__ IS_ERR (struct dentry*) ; 
 int LOOKUP_CONTINUE ; 
 int LOOKUP_DIRECTORY ; 
 int PTR_ERR (struct dentry*) ; 
 struct dentry* __d_lookup (struct dentry*,struct qstr*) ; 
 struct dentry* d_alloc (struct dentry*,struct qstr*) ; 
 struct dentry* d_lookup (struct dentry*,struct qstr*) ; 
 struct dentry* do_revalidate (struct dentry*,struct nameidata*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int follow_managed (struct path*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  path_put_conditional (struct path*,struct nameidata*) ; 
 struct dentry* stub1 (struct inode*,struct dentry*,struct nameidata*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int do_lookup(struct nameidata *nd, struct qstr *name,
		     struct path *path)
{
	struct vfsmount *mnt = nd->path.mnt;
	struct dentry *dentry = __d_lookup(nd->path.dentry, name);
	int flags = nd->flags;
	struct dentry *parent;
	struct inode *dir;
	int err;

	if (!dentry)
		goto need_lookup;
found:
	if (dentry->d_op && dentry->d_op->d_revalidate)
		goto need_revalidate;
done:
	path->mnt = mnt;
	path->dentry = dentry;
	/*
	 * Make sure follow_automount() knows about the trailing
	 * "/" but only for the real last path component.
	 */
	if (!(nd->flags & LOOKUP_CONTINUE) && name->name[name->len] == '/')
		flags |= LOOKUP_DIRECTORY;
	err = follow_managed(path, flags);
	if (unlikely(err < 0))
		path_put_conditional(path, nd);
	return err;

need_lookup:
	parent = nd->path.dentry;
	dir = parent->d_inode;

	mutex_lock(&dir->i_mutex);
	/*
	 * First re-do the cached lookup just in case it was created
	 * while we waited for the directory semaphore..
	 *
	 * FIXME! This could use version numbering or similar to
	 * avoid unnecessary cache lookups.
	 *
	 * The "dcache_lock" is purely to protect the RCU list walker
	 * from concurrent renames at this point (we mustn't get false
	 * negatives from the RCU list walk here, unlike the optimistic
	 * fast walk).
	 *
	 * so doing d_lookup() (with seqlock), instead of lockfree __d_lookup
	 */
	dentry = d_lookup(parent, name);
	if (!dentry) {
		struct dentry *new;

		/* Don't create child dentry for a dead directory. */
		dentry = ERR_PTR(-ENOENT);
		if (IS_DEADDIR(dir))
			goto out_unlock;

		new = d_alloc(parent, name);
		dentry = ERR_PTR(-ENOMEM);
		if (new) {
			dentry = dir->i_op->lookup(dir, new, nd);
			if (dentry)
				dput(new);
			else
				dentry = new;
		}
out_unlock:
		mutex_unlock(&dir->i_mutex);
		if (IS_ERR(dentry))
			goto fail;
		goto done;
	}

	/*
	 * Uhhuh! Nasty case: the cache was re-populated while
	 * we waited on the semaphore. Need to revalidate.
	 */
	mutex_unlock(&dir->i_mutex);
	goto found;

need_revalidate:
	dentry = do_revalidate(dentry, nd);
	if (!dentry)
		goto need_lookup;
	if (IS_ERR(dentry))
		goto fail;
	goto done;

fail:
	return PTR_ERR(dentry);
}