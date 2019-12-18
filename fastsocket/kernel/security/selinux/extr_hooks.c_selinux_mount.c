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
struct path {int /*<<< orphan*/  dentry; TYPE_1__* mnt; } ;
struct cred {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mnt_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  FILESYSTEM__REMOUNT ; 
 int /*<<< orphan*/  FILE__MOUNTON ; 
 unsigned long MS_REMOUNT ; 
 struct cred* current_cred () ; 
 int dentry_has_perm (struct cred const*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int superblock_has_perm (struct cred const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int selinux_mount(char *dev_name,
			 struct path *path,
			 char *type,
			 unsigned long flags,
			 void *data)
{
	const struct cred *cred = current_cred();

	if (flags & MS_REMOUNT)
		return superblock_has_perm(cred, path->mnt->mnt_sb,
					   FILESYSTEM__REMOUNT, NULL);
	else
		return dentry_has_perm(cred, path->mnt, path->dentry,
				       FILE__MOUNTON);
}