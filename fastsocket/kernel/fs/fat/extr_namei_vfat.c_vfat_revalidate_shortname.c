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
struct dentry {scalar_t__ d_time; int /*<<< orphan*/  d_lock; TYPE_2__* d_parent; } ;
struct TYPE_4__ {TYPE_1__* d_inode; } ;
struct TYPE_3__ {scalar_t__ i_version; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vfat_revalidate_shortname(struct dentry *dentry)
{
	int ret = 1;
	spin_lock(&dentry->d_lock);
	if (dentry->d_time != dentry->d_parent->d_inode->i_version)
		ret = 0;
	spin_unlock(&dentry->d_lock);
	return ret;
}