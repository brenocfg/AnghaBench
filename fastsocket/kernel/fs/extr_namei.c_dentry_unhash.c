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
struct dentry {int /*<<< orphan*/  d_lock; int /*<<< orphan*/  d_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  __d_drop (struct dentry*) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dcache_lock ; 
 int /*<<< orphan*/  dget (struct dentry*) ; 
 int /*<<< orphan*/  shrink_dcache_parent (struct dentry*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void dentry_unhash(struct dentry *dentry)
{
	dget(dentry);
	shrink_dcache_parent(dentry);
	spin_lock(&dcache_lock);
	spin_lock(&dentry->d_lock);
	if (atomic_read(&dentry->d_count) == 2)
		__d_drop(dentry);
	spin_unlock(&dentry->d_lock);
	spin_unlock(&dcache_lock);
}