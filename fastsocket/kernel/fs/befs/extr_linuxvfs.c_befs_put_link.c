#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nameidata {int dummy; } ;
struct dentry {int /*<<< orphan*/  d_inode; } ;
struct TYPE_3__ {int i_flags; } ;
typedef  TYPE_1__ befs_inode_info ;

/* Variables and functions */
 TYPE_1__* BEFS_I (int /*<<< orphan*/ ) ; 
 int BEFS_LONG_SYMLINK ; 
 int /*<<< orphan*/  IS_ERR (char*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* nd_get_link (struct nameidata*) ; 

__attribute__((used)) static void befs_put_link(struct dentry *dentry, struct nameidata *nd, void *p)
{
	befs_inode_info *befs_ino = BEFS_I(dentry->d_inode);
	if (befs_ino->i_flags & BEFS_LONG_SYMLINK) {
		char *link = nd_get_link(nd);
		if (!IS_ERR(link))
			kfree(link);
	}
}