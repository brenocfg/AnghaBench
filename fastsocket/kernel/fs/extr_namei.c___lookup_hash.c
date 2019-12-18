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
struct qstr {int dummy; } ;
struct nameidata {int dummy; } ;
struct inode {TYPE_2__* i_op; } ;
struct dentry {TYPE_1__* d_op; struct inode* d_inode; } ;
struct TYPE_4__ {struct dentry* (* lookup ) (struct inode*,struct dentry*,struct nameidata*) ;} ;
struct TYPE_3__ {int (* d_hash ) (struct dentry*,struct qstr*) ;scalar_t__ d_revalidate; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 struct dentry* ERR_PTR (int) ; 
 scalar_t__ IS_DEADDIR (struct inode*) ; 
 struct dentry* __d_lookup (struct dentry*,struct qstr*) ; 
 struct dentry* d_alloc (struct dentry*,struct qstr*) ; 
 struct dentry* d_lookup (struct dentry*,struct qstr*) ; 
 struct dentry* do_revalidate (struct dentry*,struct nameidata*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int stub1 (struct dentry*,struct qstr*) ; 
 struct dentry* stub2 (struct inode*,struct dentry*,struct nameidata*) ; 

__attribute__((used)) static struct dentry *__lookup_hash(struct qstr *name,
		struct dentry *base, struct nameidata *nd)
{
	struct dentry *dentry;
	struct inode *inode;
	int err;

	inode = base->d_inode;

	/*
	 * See if the low-level filesystem might want
	 * to use its own hash..
	 */
	if (base->d_op && base->d_op->d_hash) {
		err = base->d_op->d_hash(base, name);
		dentry = ERR_PTR(err);
		if (err < 0)
			goto out;
	}

	dentry = __d_lookup(base, name);

	/* lockess __d_lookup may fail due to concurrent d_move()
	 * in some unrelated directory, so try with d_lookup
	 */
	if (!dentry)
		dentry = d_lookup(base, name);

	if (dentry && dentry->d_op && dentry->d_op->d_revalidate)
		dentry = do_revalidate(dentry, nd);


	if (!dentry) {
		struct dentry *new;

		/* Don't create child dentry for a dead directory. */
		dentry = ERR_PTR(-ENOENT);
		if (IS_DEADDIR(inode))
			goto out;

		new = d_alloc(base, name);
		dentry = ERR_PTR(-ENOMEM);
		if (!new)
			goto out;
		dentry = inode->i_op->lookup(inode, new, nd);
		if (!dentry)
			dentry = new;
		else
			dput(new);
	}
out:
	return dentry;
}