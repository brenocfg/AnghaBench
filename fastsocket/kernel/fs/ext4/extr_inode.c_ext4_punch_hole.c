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
struct inode {int /*<<< orphan*/  i_mode; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  EXT4_INODE_EXTENTS ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int ext4_ext_punch_hole (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_test_inode_flag (struct inode*,int /*<<< orphan*/ ) ; 

int ext4_punch_hole(struct inode *inode, loff_t offset, loff_t length)
{
	if (!S_ISREG(inode->i_mode))
		return -EOPNOTSUPP;

	if (!ext4_test_inode_flag(inode, EXT4_INODE_EXTENTS)) {
		/* TODO: Add support for non extent hole punching */
		return -EOPNOTSUPP;
	}

	return ext4_ext_punch_hole(inode, offset, length);
}