#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct inode {int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_mode; } ;
struct hfs_find_data {int /*<<< orphan*/  entryoffset; int /*<<< orphan*/  bnode; TYPE_1__* search_key; } ;
struct TYPE_8__ {int /*<<< orphan*/  fdCreator; int /*<<< orphan*/  fdType; } ;
struct hfs_cat_file {TYPE_2__ UsrWds; } ;
struct dentry {struct inode* d_inode; } ;
typedef  int ssize_t ;
struct TYPE_9__ {struct hfs_cat_file file; } ;
typedef  TYPE_3__ hfs_cat_rec ;
struct TYPE_11__ {int /*<<< orphan*/  cat_key; } ;
struct TYPE_10__ {int /*<<< orphan*/  cat_tree; } ;
struct TYPE_7__ {int /*<<< orphan*/  cat; } ;

/* Variables and functions */
 int ENODATA ; 
 int EOPNOTSUPP ; 
 int ERANGE ; 
 TYPE_6__* HFS_I (struct inode*) ; 
 scalar_t__ HFS_IS_RSRC (struct inode*) ; 
 TYPE_5__* HFS_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hfs_bnode_read (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int hfs_brec_find (struct hfs_find_data*) ; 
 int /*<<< orphan*/  hfs_find_exit (struct hfs_find_data*) ; 
 int hfs_find_init (int /*<<< orphan*/ ,struct hfs_find_data*) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

ssize_t hfs_getxattr(struct dentry *dentry, const char *name,
			 void *value, size_t size)
{
	struct inode *inode = dentry->d_inode;
	struct hfs_find_data fd;
	hfs_cat_rec rec;
	struct hfs_cat_file *file;
	ssize_t res = 0;

	if (!S_ISREG(inode->i_mode) || HFS_IS_RSRC(inode))
		return -EOPNOTSUPP;

	if (size) {
		res = hfs_find_init(HFS_SB(inode->i_sb)->cat_tree, &fd);
		if (res)
			return res;
		fd.search_key->cat = HFS_I(inode)->cat_key;
		res = hfs_brec_find(&fd);
		if (res)
			goto out;
		hfs_bnode_read(fd.bnode, &rec, fd.entryoffset,
				sizeof(struct hfs_cat_file));
	}
	file = &rec.file;

	if (!strcmp(name, "hfs.type")) {
		if (size >= 4) {
			memcpy(value, &file->UsrWds.fdType, 4);
			res = 4;
		} else
			res = size ? -ERANGE : 4;
	} else if (!strcmp(name, "hfs.creator")) {
		if (size >= 4) {
			memcpy(value, &file->UsrWds.fdCreator, 4);
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