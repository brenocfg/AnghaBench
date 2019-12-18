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
struct dentry {TYPE_1__ d_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*,struct dentry*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ autofs4_can_expire (struct dentry*,unsigned long,int) ; 
 scalar_t__ autofs4_mount_busy (struct vfsmount*,struct dentry*) ; 
 scalar_t__ d_mountpoint (struct dentry*) ; 
 int /*<<< orphan*/  dcache_lock ; 
 struct dentry* dget (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 struct dentry* next_dentry (struct dentry*,struct dentry*) ; 
 int /*<<< orphan*/  simple_positive (struct dentry*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct dentry *autofs4_check_leaves(struct vfsmount *mnt,
					   struct dentry *parent,
					   unsigned long timeout,
					   int do_now)
{
	struct dentry *p;

	DPRINTK("parent %p %.*s",
		parent, (int)parent->d_name.len, parent->d_name.name);

	spin_lock(&dcache_lock);
	for (p = parent; p; p = next_dentry(p, parent)) {
		/* Negative dentry - give up */
		if (!simple_positive(p))
			continue;

		DPRINTK("dentry %p %.*s",
			p, (int) p->d_name.len, p->d_name.name);

		p = dget(p);
		spin_unlock(&dcache_lock);

		if (d_mountpoint(p)) {
			/* Can we umount this guy */
			if (autofs4_mount_busy(mnt, p))
				goto cont;

			/* Can we expire this guy */
			if (autofs4_can_expire(p, timeout, do_now))
				return p;
		}
cont:
		dput(p);
		spin_lock(&dcache_lock);
	}
	spin_unlock(&dcache_lock);
	return NULL;
}