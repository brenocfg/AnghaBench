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
struct inode {int /*<<< orphan*/  i_ino; } ;
struct hfs_find_data {int /*<<< orphan*/  entrylength; int /*<<< orphan*/  entryoffset; int /*<<< orphan*/  bnode; int /*<<< orphan*/  search_key; } ;
typedef  int /*<<< orphan*/  hfs_extent_rec ;
struct TYPE_2__ {int flags; int /*<<< orphan*/  cached_extents; int /*<<< orphan*/  cached_start; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  HFS_FK_DATA ; 
 int /*<<< orphan*/  HFS_FK_RSRC ; 
 int HFS_FLG_EXT_DIRTY ; 
 int HFS_FLG_EXT_NEW ; 
 TYPE_1__* HFS_I (struct inode*) ; 
 scalar_t__ HFS_IS_RSRC (struct inode*) ; 
 int /*<<< orphan*/  hfs_bnode_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int hfs_brec_find (struct hfs_find_data*) ; 
 int /*<<< orphan*/  hfs_brec_insert (struct hfs_find_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hfs_ext_build_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __hfs_ext_write_extent(struct inode *inode, struct hfs_find_data *fd)
{
	int res;

	hfs_ext_build_key(fd->search_key, inode->i_ino, HFS_I(inode)->cached_start,
			  HFS_IS_RSRC(inode) ?  HFS_FK_RSRC : HFS_FK_DATA);
	res = hfs_brec_find(fd);
	if (HFS_I(inode)->flags & HFS_FLG_EXT_NEW) {
		if (res != -ENOENT)
			return;
		hfs_brec_insert(fd, HFS_I(inode)->cached_extents, sizeof(hfs_extent_rec));
		HFS_I(inode)->flags &= ~(HFS_FLG_EXT_DIRTY|HFS_FLG_EXT_NEW);
	} else {
		if (res)
			return;
		hfs_bnode_write(fd->bnode, HFS_I(inode)->cached_extents, fd->entryoffset, fd->entrylength);
		HFS_I(inode)->flags &= ~HFS_FLG_EXT_DIRTY;
	}
}