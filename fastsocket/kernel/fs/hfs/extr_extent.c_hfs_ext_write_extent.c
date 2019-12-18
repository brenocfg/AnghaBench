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
struct inode {int /*<<< orphan*/  i_sb; } ;
struct hfs_find_data {int dummy; } ;
struct TYPE_4__ {int flags; } ;
struct TYPE_3__ {int /*<<< orphan*/  ext_tree; } ;

/* Variables and functions */
 int HFS_FLG_EXT_DIRTY ; 
 TYPE_2__* HFS_I (struct inode*) ; 
 TYPE_1__* HFS_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __hfs_ext_write_extent (struct inode*,struct hfs_find_data*) ; 
 int /*<<< orphan*/  hfs_find_exit (struct hfs_find_data*) ; 
 int /*<<< orphan*/  hfs_find_init (int /*<<< orphan*/ ,struct hfs_find_data*) ; 

void hfs_ext_write_extent(struct inode *inode)
{
	struct hfs_find_data fd;

	if (HFS_I(inode)->flags & HFS_FLG_EXT_DIRTY) {
		hfs_find_init(HFS_SB(inode->i_sb)->ext_tree, &fd);
		__hfs_ext_write_extent(inode, &fd);
		hfs_find_exit(&fd);
	}
}