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
struct file_operations {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int __oprofilefs_create_file (struct super_block*,struct dentry*,char const*,struct file_operations const*,int,int /*<<< orphan*/ *) ; 

int oprofilefs_create_file(struct super_block *sb, struct dentry *root,
	char const *name, const struct file_operations *fops)
{
	return __oprofilefs_create_file(sb, root, name, fops, 0644, NULL);
}