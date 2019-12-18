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
 int /*<<< orphan*/  ENOMEM ; 
 struct dentry* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct dentry*) ; 
 int REG_FILE_MODE ; 
 int S_IFREG ; 
 int /*<<< orphan*/  hypfs_add_dentry (struct dentry*) ; 
 struct dentry* hypfs_create_file (struct super_block*,struct dentry*,char const*,char*,int) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 scalar_t__ strlen (char*) ; 

struct dentry *hypfs_create_str(struct super_block *sb, struct dentry *dir,
				const char *name, char *string)
{
	char *buffer;
	struct dentry *dentry;

	buffer = kmalloc(strlen(string) + 2, GFP_KERNEL);
	if (!buffer)
		return ERR_PTR(-ENOMEM);
	sprintf(buffer, "%s\n", string);
	dentry =
	    hypfs_create_file(sb, dir, name, buffer, S_IFREG | REG_FILE_MODE);
	if (IS_ERR(dentry)) {
		kfree(buffer);
		return ERR_PTR(-ENOMEM);
	}
	hypfs_add_dentry(dentry);
	return dentry;
}