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
struct inode {int /*<<< orphan*/  i_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXT4_FEATURE_COMPAT_DIR_INDEX ; 
 int /*<<< orphan*/  EXT4_HAS_COMPAT_FEATURE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXT4_INODE_INDEX ; 
 int /*<<< orphan*/  ext4_clear_inode_flag (struct inode*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ext4_update_dx_flag(struct inode *inode)
{
	if (!EXT4_HAS_COMPAT_FEATURE(inode->i_sb,
				     EXT4_FEATURE_COMPAT_DIR_INDEX))
		ext4_clear_inode_flag(inode, EXT4_INODE_INDEX);
}