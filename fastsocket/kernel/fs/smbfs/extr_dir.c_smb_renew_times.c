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
struct dentry {int /*<<< orphan*/  d_lock; struct dentry* d_parent; int /*<<< orphan*/  d_time; } ;

/* Variables and functions */
 scalar_t__ IS_ROOT (struct dentry*) ; 
 int /*<<< orphan*/  dget (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void
smb_renew_times(struct dentry * dentry)
{
	dget(dentry);
	spin_lock(&dentry->d_lock);
	for (;;) {
		struct dentry *parent;

		dentry->d_time = jiffies;
		if (IS_ROOT(dentry))
			break;
		parent = dentry->d_parent;
		dget(parent);
		spin_unlock(&dentry->d_lock);
		dput(dentry);
		dentry = parent;
		spin_lock(&dentry->d_lock);
	}
	spin_unlock(&dentry->d_lock);
	dput(dentry);
}