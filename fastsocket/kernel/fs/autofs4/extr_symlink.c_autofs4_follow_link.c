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
struct nameidata {int dummy; } ;
struct dentry {int dummy; } ;
struct TYPE_2__ {scalar_t__ symlink; } ;
struct autofs_info {TYPE_1__ u; } ;

/* Variables and functions */
 struct autofs_info* autofs4_dentry_ino (struct dentry*) ; 
 int /*<<< orphan*/  nd_set_link (struct nameidata*,char*) ; 

__attribute__((used)) static void *autofs4_follow_link(struct dentry *dentry, struct nameidata *nd)
{
	struct autofs_info *ino = autofs4_dentry_ino(dentry);
	nd_set_link(nd, (char *)ino->u.symlink);
	return NULL;
}