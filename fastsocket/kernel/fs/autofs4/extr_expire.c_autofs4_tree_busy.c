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
struct vfsmount {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; scalar_t__ len; } ;
struct dentry {int /*<<< orphan*/  d_count; TYPE_1__ d_name; } ;
struct autofs_info {void* last_used; int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*,struct dentry*,int,int /*<<< orphan*/ ) ; 
 unsigned int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  autofs4_can_expire (struct dentry*,unsigned long,int) ; 
 struct autofs_info* autofs4_dentry_ino (struct dentry*) ; 
 scalar_t__ autofs4_mount_busy (struct vfsmount*,struct dentry*) ; 
 int /*<<< orphan*/  d_invalidate (struct dentry*) ; 
 scalar_t__ d_mountpoint (struct dentry*) ; 
 int /*<<< orphan*/  dcache_lock ; 
 struct dentry* dget (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 void* jiffies ; 
 struct dentry* next_dentry (struct dentry*,struct dentry*) ; 
 int /*<<< orphan*/  simple_positive (struct dentry*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int autofs4_tree_busy(struct vfsmount *mnt,
	       		     struct dentry *top,
			     unsigned long timeout,
			     int do_now)
{
	struct autofs_info *top_ino = autofs4_dentry_ino(top);
	struct dentry *p;

	DPRINTK("top %p %.*s",
		top, (int)top->d_name.len, top->d_name.name);

	/* Negative dentry - give up */
	if (!simple_positive(top))
		return 1;

	spin_lock(&dcache_lock);
	for (p = top; p; p = next_dentry(p, top)) {
		/* Negative dentry - give up */
		if (!simple_positive(p))
			continue;

		DPRINTK("dentry %p %.*s",
			p, (int) p->d_name.len, p->d_name.name);

		p = dget(p);
		spin_unlock(&dcache_lock);

		/*
		 * Is someone visiting anywhere in the subtree ?
		 * If there's no mount we need to check the usage
		 * count for the autofs dentry.
		 * If the fs is busy update the expiry counter.
		 */
		if (d_mountpoint(p)) {
			if (autofs4_mount_busy(mnt, p)) {
				top_ino->last_used = jiffies;
				dput(p);
				return 1;
			}
		} else {
			struct autofs_info *ino = autofs4_dentry_ino(p);
			unsigned int ino_count = atomic_read(&ino->count);

			/*
			 * Clean stale dentries below that have not been
			 * invalidated after a mount fail during lookup
			 */
			d_invalidate(p);

			/* allow for dget above and top is already dgot */
			if (p == top)
				ino_count += 2;
			else
				ino_count++;

			if (atomic_read(&p->d_count) > ino_count) {
				top_ino->last_used = jiffies;
				dput(p);
				return 1;
			}
		}
		dput(p);
		spin_lock(&dcache_lock);
	}
	spin_unlock(&dcache_lock);

	/* Timeout of a tree mount is ultimately determined by its top dentry */
	if (!autofs4_can_expire(top, timeout, do_now))
		return 1;

	return 0;
}