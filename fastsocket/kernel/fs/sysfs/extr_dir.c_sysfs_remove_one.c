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
struct TYPE_2__ {struct sysfs_dirent* removed_list; } ;
struct sysfs_dirent {int s_flags; TYPE_1__ u; } ;
struct sysfs_addrm_cxt {int /*<<< orphan*/  cnt; scalar_t__ parent_inode; struct sysfs_dirent* removed; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ SYSFS_DIR ; 
 int SYSFS_FLAG_REMOVED ; 
 int /*<<< orphan*/  drop_nlink (scalar_t__) ; 
 scalar_t__ sysfs_type (struct sysfs_dirent*) ; 
 int /*<<< orphan*/  sysfs_unlink_sibling (struct sysfs_dirent*) ; 

void sysfs_remove_one(struct sysfs_addrm_cxt *acxt, struct sysfs_dirent *sd)
{
	BUG_ON(sd->s_flags & SYSFS_FLAG_REMOVED);

	sysfs_unlink_sibling(sd);

	sd->s_flags |= SYSFS_FLAG_REMOVED;
	sd->u.removed_list = acxt->removed;
	acxt->removed = sd;

	if (sysfs_type(sd) == SYSFS_DIR && acxt->parent_inode)
		drop_nlink(acxt->parent_inode);

	acxt->cnt++;
}