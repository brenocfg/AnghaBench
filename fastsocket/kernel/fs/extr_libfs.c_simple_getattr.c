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
struct kstat {int blocks; } ;
struct inode {TYPE_1__* i_mapping; } ;
struct dentry {struct inode* d_inode; } ;
struct TYPE_2__ {int nrpages; } ;

/* Variables and functions */
 int PAGE_CACHE_SHIFT ; 
 int /*<<< orphan*/  generic_fillattr (struct inode*,struct kstat*) ; 

int simple_getattr(struct vfsmount *mnt, struct dentry *dentry,
		   struct kstat *stat)
{
	struct inode *inode = dentry->d_inode;
	generic_fillattr(inode, stat);
	stat->blocks = inode->i_mapping->nrpages << (PAGE_CACHE_SHIFT - 9);
	return 0;
}