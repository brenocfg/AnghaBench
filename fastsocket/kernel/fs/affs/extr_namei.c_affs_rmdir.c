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
typedef  int /*<<< orphan*/  u32 ;
struct inode {scalar_t__ i_ino; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; scalar_t__ len; } ;
struct dentry {TYPE_2__ d_name; TYPE_1__* d_inode; } ;
struct TYPE_3__ {int /*<<< orphan*/  i_ino; } ;

/* Variables and functions */
 int affs_remove_header (struct dentry*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int
affs_rmdir(struct inode *dir, struct dentry *dentry)
{
	pr_debug("AFFS: rmdir(dir=%u, %lu \"%.*s\")\n", (u32)dir->i_ino,
		 dentry->d_inode->i_ino,
		 (int)dentry->d_name.len, dentry->d_name.name);

	return affs_remove_header(dentry);
}