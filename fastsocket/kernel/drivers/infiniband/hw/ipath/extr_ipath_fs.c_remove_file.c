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
struct dentry {int /*<<< orphan*/  d_lock; scalar_t__ d_inode; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct dentry*) ; 
 int PTR_ERR (struct dentry*) ; 
 int /*<<< orphan*/  __d_drop (struct dentry*) ; 
 scalar_t__ d_unhashed (struct dentry*) ; 
 int /*<<< orphan*/  dcache_lock ; 
 int /*<<< orphan*/  dget_locked (struct dentry*) ; 
 struct dentry* lookup_one_len (char*,struct dentry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  simple_unlink (scalar_t__,struct dentry*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static int remove_file(struct dentry *parent, char *name)
{
	struct dentry *tmp;
	int ret;

	tmp = lookup_one_len(name, parent, strlen(name));

	if (IS_ERR(tmp)) {
		ret = PTR_ERR(tmp);
		goto bail;
	}

	spin_lock(&dcache_lock);
	spin_lock(&tmp->d_lock);
	if (!(d_unhashed(tmp) && tmp->d_inode)) {
		dget_locked(tmp);
		__d_drop(tmp);
		spin_unlock(&tmp->d_lock);
		spin_unlock(&dcache_lock);
		simple_unlink(parent->d_inode, tmp);
	} else {
		spin_unlock(&tmp->d_lock);
		spin_unlock(&dcache_lock);
	}

	ret = 0;
bail:
	/*
	 * We don't expect clients to care about the return value, but
	 * it's there if they need it.
	 */
	return ret;
}