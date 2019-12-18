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
struct super_block {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int S_IFREG ; 
 int UPDATE_FILE_MODE ; 
 struct dentry* hypfs_create_file (struct super_block*,struct dentry*,char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static struct dentry *hypfs_create_update_file(struct super_block *sb,
					       struct dentry *dir)
{
	struct dentry *dentry;

	dentry = hypfs_create_file(sb, dir, "update", NULL,
				   S_IFREG | UPDATE_FILE_MODE);
	/*
	 * We do not put the update file on the 'delete' list with
	 * hypfs_add_dentry(), since it should not be removed when the tree
	 * is updated.
	 */
	return dentry;
}