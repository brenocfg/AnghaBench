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
struct inode {int dummy; } ;
struct btrfs_root {TYPE_1__* fs_info; } ;
struct TYPE_5__ {scalar_t__ objectid; } ;
struct TYPE_6__ {TYPE_2__ location; } ;
struct TYPE_4__ {struct btrfs_root* tree_root; } ;

/* Variables and functions */
 scalar_t__ BTRFS_FREE_INO_OBJECTID ; 
 TYPE_3__* BTRFS_I (struct inode*) ; 

__attribute__((used)) static inline bool btrfs_is_free_space_inode(struct btrfs_root *root,
				       struct inode *inode)
{
	if (root == root->fs_info->tree_root ||
	    BTRFS_I(inode)->location.objectid == BTRFS_FREE_INO_OBJECTID)
		return true;
	return false;
}