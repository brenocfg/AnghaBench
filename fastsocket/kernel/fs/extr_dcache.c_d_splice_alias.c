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
struct inode {int /*<<< orphan*/  i_mode; } ;
struct dentry {int /*<<< orphan*/  d_parent; } ;

/* Variables and functions */
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __d_instantiate (struct dentry*,struct inode*) ; 
 struct dentry* __find_moveable_alias (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d_add (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  d_move (struct dentry*,struct dentry*) ; 
 int /*<<< orphan*/  d_rehash (struct dentry*) ; 
 int /*<<< orphan*/  dcache_lock ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  security_d_instantiate (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

struct dentry *d_splice_alias(struct inode *inode, struct dentry *dentry)
{
	struct dentry *new = NULL;

	if (inode && S_ISDIR(inode->i_mode)) {
		spin_lock(&dcache_lock);
		new = __find_moveable_alias(inode, dentry->d_parent);
		if (new) {
			spin_unlock(&dcache_lock);
			security_d_instantiate(new, inode);
			d_rehash(dentry);
			d_move(new, dentry);
			iput(inode);
		} else {
			/* already taking dcache_lock, so d_add() by hand */
			__d_instantiate(dentry, inode);
			spin_unlock(&dcache_lock);
			security_d_instantiate(dentry, inode);
			d_rehash(dentry);
		}
	} else
		d_add(dentry, inode);
	return new;
}