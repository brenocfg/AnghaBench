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
 int HFSPLUS_FLG_EXT_DIRTY ; 
 TYPE_2__ HFSPLUS_I (struct inode*) ; 
 TYPE_1__ HFSPLUS_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __hfsplus_ext_write_extent (struct inode*,struct hfs_find_data*) ; 
 int /*<<< orphan*/  hfs_find_exit (struct hfs_find_data*) ; 
 int /*<<< orphan*/  hfs_find_init (int /*<<< orphan*/ ,struct hfs_find_data*) ; 

void hfsplus_ext_write_extent(struct inode *inode)
{
	if (HFSPLUS_I(inode).flags & HFSPLUS_FLG_EXT_DIRTY) {
		struct hfs_find_data fd;

		hfs_find_init(HFSPLUS_SB(inode->i_sb).ext_tree, &fd);
		__hfsplus_ext_write_extent(inode, &fd);
		hfs_find_exit(&fd);
	}
}