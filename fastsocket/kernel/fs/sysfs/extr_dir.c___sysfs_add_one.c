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
struct sysfs_dirent {int /*<<< orphan*/  s_parent; int /*<<< orphan*/  s_name; } ;
struct sysfs_addrm_cxt {int /*<<< orphan*/  cnt; scalar_t__ parent_inode; int /*<<< orphan*/  parent_sd; } ;

/* Variables and functions */
 int EEXIST ; 
 scalar_t__ SYSFS_DIR ; 
 int /*<<< orphan*/  inc_nlink (scalar_t__) ; 
 scalar_t__ sysfs_find_dirent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysfs_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysfs_link_sibling (struct sysfs_dirent*) ; 
 scalar_t__ sysfs_type (struct sysfs_dirent*) ; 

int __sysfs_add_one(struct sysfs_addrm_cxt *acxt, struct sysfs_dirent *sd)
{
	if (sysfs_find_dirent(acxt->parent_sd, sd->s_name))
		return -EEXIST;

	sd->s_parent = sysfs_get(acxt->parent_sd);

	if (sysfs_type(sd) == SYSFS_DIR && acxt->parent_inode)
		inc_nlink(acxt->parent_inode);

	acxt->cnt++;

	sysfs_link_sibling(sd);

	return 0;
}