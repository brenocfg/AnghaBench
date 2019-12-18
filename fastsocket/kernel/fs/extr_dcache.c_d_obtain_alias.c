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
struct qstr {char* name; } ;
struct inode {int /*<<< orphan*/  d_lock; TYPE_1__* i_sb; int /*<<< orphan*/  d_hash; int /*<<< orphan*/  i_dentry; int /*<<< orphan*/  d_alias; int /*<<< orphan*/  d_flags; struct inode* d_inode; TYPE_1__* d_sb; struct inode* d_parent; } ;
struct dentry {int /*<<< orphan*/  d_lock; TYPE_1__* i_sb; int /*<<< orphan*/  d_hash; int /*<<< orphan*/  i_dentry; int /*<<< orphan*/  d_alias; int /*<<< orphan*/  d_flags; struct dentry* d_inode; TYPE_1__* d_sb; struct dentry* d_parent; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_anon; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCACHE_DISCONNECTED ; 
 int /*<<< orphan*/  DCACHE_UNHASHED ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct inode* ERR_CAST (struct inode*) ; 
 struct inode* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESTALE ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 struct inode* __d_find_any_alias (struct inode*) ; 
 struct inode* d_alloc (int /*<<< orphan*/ *,struct qstr const*) ; 
 struct inode* d_find_any_alias (struct inode*) ; 
 int /*<<< orphan*/  dcache_lock ; 
 int /*<<< orphan*/  dput (struct inode*) ; 
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  security_d_instantiate (struct inode*,struct inode*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

struct dentry *d_obtain_alias(struct inode *inode)
{
	static const struct qstr anonstring = { .name = "" };
	struct dentry *tmp;
	struct dentry *res;

	if (!inode)
		return ERR_PTR(-ESTALE);
	if (IS_ERR(inode))
		return ERR_CAST(inode);

	res = d_find_any_alias(inode);
	if (res)
		goto out_iput;

	tmp = d_alloc(NULL, &anonstring);
	if (!tmp) {
		res = ERR_PTR(-ENOMEM);
		goto out_iput;
	}
	tmp->d_parent = tmp; /* make sure dput doesn't croak */

	spin_lock(&dcache_lock);
	res = __d_find_any_alias(inode);
	if (res) {
		spin_unlock(&dcache_lock);
		dput(tmp);
		goto out_iput;
	}

	/* attach a disconnected dentry */
	spin_lock(&tmp->d_lock);
	tmp->d_sb = inode->i_sb;
	tmp->d_inode = inode;
	tmp->d_flags |= DCACHE_DISCONNECTED;
	tmp->d_flags &= ~DCACHE_UNHASHED;
	list_add(&tmp->d_alias, &inode->i_dentry);
	hlist_add_head(&tmp->d_hash, &inode->i_sb->s_anon);
	spin_unlock(&tmp->d_lock);
	spin_unlock(&dcache_lock);

	security_d_instantiate(tmp, inode);
	return tmp;

 out_iput:
	if (res && !IS_ERR(res))
		security_d_instantiate(res, inode);
	iput(inode);
	return res;
}