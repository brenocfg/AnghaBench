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
struct inode {int dummy; } ;
struct ext4_ext_path {scalar_t__ p_bh; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int ext4_handle_dirty_metadata (int /*<<< orphan*/ *,struct inode*,scalar_t__) ; 
 int ext4_mark_inode_dirty (int /*<<< orphan*/ *,struct inode*) ; 

__attribute__((used)) static int ext4_ext_dirty(handle_t *handle, struct inode *inode,
				struct ext4_ext_path *path)
{
	int err;
	if (path->p_bh) {
		/* path points to block */
		err = ext4_handle_dirty_metadata(handle, inode, path->p_bh);
	} else {
		/* path points to leaf/index in inode body */
		err = ext4_mark_inode_dirty(handle, inode);
	}
	return err;
}