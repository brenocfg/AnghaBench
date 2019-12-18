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
struct inode {int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_sb; } ;
typedef  scalar_t__ sector_t ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  EXT4_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __ext4_error (int /*<<< orphan*/ ,char const*,char*,int /*<<< orphan*/ ,unsigned long long,unsigned long long,int) ; 
 int /*<<< orphan*/  ext4_data_block_valid (int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static int check_block_validity(struct inode *inode, const char *msg,
				sector_t logical, sector_t phys, int len)
{
	if (!ext4_data_block_valid(EXT4_SB(inode->i_sb), phys, len)) {
		__ext4_error(inode->i_sb, msg,
			   "inode #%lu logical block %llu mapped to %llu "
			   "(size %d)", inode->i_ino,
			   (unsigned long long) logical,
			   (unsigned long long) phys, len);
		return -EIO;
	}
	return 0;
}