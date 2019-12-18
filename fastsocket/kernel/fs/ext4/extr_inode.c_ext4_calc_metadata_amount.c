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
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXT4_INODE_EXTENTS ; 
 int ext4_ext_calc_metadata_amount (struct inode*,int /*<<< orphan*/ ) ; 
 int ext4_indirect_calc_metadata_amount (struct inode*,int /*<<< orphan*/ ) ; 
 scalar_t__ ext4_test_inode_flag (struct inode*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ext4_calc_metadata_amount(struct inode *inode, sector_t lblock)
{
	if (ext4_test_inode_flag(inode, EXT4_INODE_EXTENTS))
		return ext4_ext_calc_metadata_amount(inode, lblock);

	return ext4_indirect_calc_metadata_amount(inode, lblock);
}