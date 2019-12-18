#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct inode {int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_mode; } ;
struct TYPE_5__ {int /*<<< orphan*/  fdCreator; int /*<<< orphan*/  fdType; } ;
struct hfsplus_cat_file {TYPE_1__ user_info; } ;
struct hfs_find_data {int /*<<< orphan*/  entryoffset; int /*<<< orphan*/  bnode; } ;
struct dentry {struct inode* d_inode; } ;
typedef  int ssize_t ;
struct TYPE_6__ {struct hfsplus_cat_file file; } ;
typedef  TYPE_2__ hfsplus_cat_entry ;
struct TYPE_7__ {int /*<<< orphan*/  cat_tree; } ;

/* Variables and functions */
 int ENODATA ; 
 int EOPNOTSUPP ; 
 int ERANGE ; 
 scalar_t__ HFSPLUS_IS_RSRC (struct inode*) ; 
 TYPE_4__ HFSPLUS_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hfs_bnode_read (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hfs_find_exit (struct hfs_find_data*) ; 
 int hfs_find_init (int /*<<< orphan*/ ,struct hfs_find_data*) ; 
 int hfsplus_find_cat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hfs_find_data*) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

ssize_t hfsplus_getxattr(struct dentry *dentry, const char *name,
			 void *value, size_t size)
{
	struct inode *inode = dentry->d_inode;
	struct hfs_find_data fd;
	hfsplus_cat_entry entry;
	struct hfsplus_cat_file *file;
	ssize_t res = 0;

	if (!S_ISREG(inode->i_mode) || HFSPLUS_IS_RSRC(inode))
		return -EOPNOTSUPP;

	if (size) {
		res = hfs_find_init(HFSPLUS_SB(inode->i_sb).cat_tree, &fd);
		if (res)
			return res;
		res = hfsplus_find_cat(inode->i_sb, inode->i_ino, &fd);
		if (res)
			goto out;
		hfs_bnode_read(fd.bnode, &entry, fd.entryoffset,
				sizeof(struct hfsplus_cat_file));
	}
	file = &entry.file;

	if (!strcmp(name, "hfs.type")) {
		if (size >= 4) {
			memcpy(value, &file->user_info.fdType, 4);
			res = 4;
		} else
			res = size ? -ERANGE : 4;
	} else if (!strcmp(name, "hfs.creator")) {
		if (size >= 4) {
			memcpy(value, &file->user_info.fdCreator, 4);
			res = 4;
		} else
			res = size ? -ERANGE : 4;
	} else
		res = -ENODATA;
out:
	if (size)
		hfs_find_exit(&fd);
	return res;
}