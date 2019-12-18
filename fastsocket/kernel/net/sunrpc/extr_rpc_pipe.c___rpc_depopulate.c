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
struct rpc_filelist {int /*<<< orphan*/  name; } ;
struct qstr {int /*<<< orphan*/  len; int /*<<< orphan*/  name; int /*<<< orphan*/  hash; } ;
struct inode {int i_mode; } ;
struct dentry {struct inode* d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  S_IFDIR 129 
 int S_IFMT ; 
#define  S_IFREG 128 
 int /*<<< orphan*/  __rpc_rmdir (struct inode*,struct dentry*) ; 
 int /*<<< orphan*/  __rpc_unlink (struct inode*,struct dentry*) ; 
 struct dentry* d_lookup (struct dentry*,struct qstr*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  full_name_hash (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __rpc_depopulate(struct dentry *parent,
			     const struct rpc_filelist *files,
			     int start, int eof)
{
	struct inode *dir = parent->d_inode;
	struct dentry *dentry;
	struct qstr name;
	int i;

	for (i = start; i < eof; i++) {
		name.name = files[i].name;
		name.len = strlen(files[i].name);
		name.hash = full_name_hash(name.name, name.len);
		dentry = d_lookup(parent, &name);

		if (dentry == NULL)
			continue;
		if (dentry->d_inode == NULL)
			goto next;
		switch (dentry->d_inode->i_mode & S_IFMT) {
			default:
				BUG();
			case S_IFREG:
				__rpc_unlink(dir, dentry);
				break;
			case S_IFDIR:
				__rpc_rmdir(dir, dentry);
		}
next:
		dput(dentry);
	}
}