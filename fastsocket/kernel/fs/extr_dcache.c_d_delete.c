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
struct dentry {int /*<<< orphan*/  d_lock; int /*<<< orphan*/  d_count; TYPE_1__* d_inode; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_mode; } ;

/* Variables and functions */
 int S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __d_drop (struct dentry*) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  d_unhashed (struct dentry*) ; 
 int /*<<< orphan*/  dcache_lock ; 
 int /*<<< orphan*/  dentry_iput (struct dentry*) ; 
 int /*<<< orphan*/  fsnotify_nameremove (struct dentry*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void d_delete(struct dentry * dentry)
{
	int isdir = 0;
	/*
	 * Are we the only user?
	 */
	spin_lock(&dcache_lock);
	spin_lock(&dentry->d_lock);
	isdir = S_ISDIR(dentry->d_inode->i_mode);
	if (atomic_read(&dentry->d_count) == 1) {
		dentry_iput(dentry);
		fsnotify_nameremove(dentry, isdir);
		return;
	}

	if (!d_unhashed(dentry))
		__d_drop(dentry);

	spin_unlock(&dentry->d_lock);
	spin_unlock(&dcache_lock);

	fsnotify_nameremove(dentry, isdir);
}