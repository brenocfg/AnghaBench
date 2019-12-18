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
struct qstr {char const* name; scalar_t__ len; int /*<<< orphan*/  hash; } ;
struct inode {int dummy; } ;
struct dentry {struct inode* d_inode; struct qstr d_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  POHMELFS_I (struct inode*) ; 
 int S_IFLNK ; 
 int S_IRWXG ; 
 int S_IRWXO ; 
 int S_IRWXU ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  jhash (char const*,scalar_t__,int /*<<< orphan*/ ) ; 
 int page_symlink (struct inode*,char const*,scalar_t__) ; 
 int pohmelfs_create_entry (struct inode*,struct dentry*,int /*<<< orphan*/ ,int) ; 
 int pohmelfs_create_link (int /*<<< orphan*/ ,struct qstr*,int /*<<< orphan*/ *,struct qstr*) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static int pohmelfs_symlink(struct inode *dir, struct dentry *dentry, const char *symname)
{
	struct qstr sym_str;
	struct qstr str = dentry->d_name;
	struct inode *inode;
	int err;

	str.hash = jhash(dentry->d_name.name, dentry->d_name.len, 0);

	sym_str.name = symname;
	sym_str.len = strlen(symname);

	err = pohmelfs_create_link(POHMELFS_I(dir), &str, NULL, &sym_str);
	if (err)
		goto err_out_exit;

	err = pohmelfs_create_entry(dir, dentry, 0, S_IFLNK | S_IRWXU | S_IRWXG | S_IRWXO);
	if (err)
		goto err_out_exit;

	inode = dentry->d_inode;

	err = page_symlink(inode, symname, sym_str.len + 1);
	if (err)
		goto err_out_put;

	return 0;

err_out_put:
	iput(inode);
err_out_exit:
	return err;
}