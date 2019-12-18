#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct inode {int /*<<< orphan*/  i_ino; } ;
struct hfs_find_data {TYPE_2__* key; } ;
struct TYPE_6__ {int flags; scalar_t__ cached_blocks; scalar_t__ cached_start; int /*<<< orphan*/  cached_extents; } ;
struct TYPE_4__ {int /*<<< orphan*/  FABN; } ;
struct TYPE_5__ {TYPE_1__ ext; } ;

/* Variables and functions */
 int /*<<< orphan*/  HFS_FK_DATA ; 
 int /*<<< orphan*/  HFS_FK_RSRC ; 
 int HFS_FLG_EXT_DIRTY ; 
 int HFS_FLG_EXT_NEW ; 
 TYPE_3__* HFS_I (struct inode*) ; 
 scalar_t__ HFS_IS_RSRC (struct inode*) ; 
 int __hfs_ext_read_extent (struct hfs_find_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __hfs_ext_write_extent (struct inode*,struct hfs_find_data*) ; 
 scalar_t__ be16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ hfs_ext_block_count (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int __hfs_ext_cache_extent(struct hfs_find_data *fd, struct inode *inode, u32 block)
{
	int res;

	if (HFS_I(inode)->flags & HFS_FLG_EXT_DIRTY)
		__hfs_ext_write_extent(inode, fd);

	res = __hfs_ext_read_extent(fd, HFS_I(inode)->cached_extents, inode->i_ino,
				    block, HFS_IS_RSRC(inode) ? HFS_FK_RSRC : HFS_FK_DATA);
	if (!res) {
		HFS_I(inode)->cached_start = be16_to_cpu(fd->key->ext.FABN);
		HFS_I(inode)->cached_blocks = hfs_ext_block_count(HFS_I(inode)->cached_extents);
	} else {
		HFS_I(inode)->cached_start = HFS_I(inode)->cached_blocks = 0;
		HFS_I(inode)->flags &= ~(HFS_FLG_EXT_DIRTY|HFS_FLG_EXT_NEW);
	}
	return res;
}