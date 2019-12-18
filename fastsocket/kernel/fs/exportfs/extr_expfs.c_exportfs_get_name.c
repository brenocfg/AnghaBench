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
struct export_operations {int (* get_name ) (struct dentry*,char*,struct dentry*) ;} ;
struct dentry {TYPE_1__* d_sb; } ;
struct TYPE_2__ {struct export_operations* s_export_op; } ;

/* Variables and functions */
 int get_name (struct vfsmount*,struct dentry*,char*,struct dentry*) ; 
 int stub1 (struct dentry*,char*,struct dentry*) ; 

__attribute__((used)) static int exportfs_get_name(struct vfsmount *mnt, struct dentry *dir,
		char *name, struct dentry *child)
{
	const struct export_operations *nop = dir->d_sb->s_export_op;

	if (nop->get_name)
		return nop->get_name(dir, name, child);
	else
		return get_name(mnt, dir, name, child);
}