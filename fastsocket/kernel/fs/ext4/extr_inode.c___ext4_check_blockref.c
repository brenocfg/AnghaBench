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
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  EXT4_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __ext4_error (int /*<<< orphan*/ ,char const*,char*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_data_block_valid (int /*<<< orphan*/ ,unsigned int,int) ; 
 unsigned int le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int __ext4_check_blockref(const char *function, struct inode *inode,
				 __le32 *p, unsigned int max)
{
	__le32 *bref = p;
	unsigned int blk;

	while (bref < p+max) {
		blk = le32_to_cpu(*bref++);
		if (blk &&
		    unlikely(!ext4_data_block_valid(EXT4_SB(inode->i_sb),
						    blk, 1))) {
			__ext4_error(inode->i_sb, function,
				   "invalid block reference %u "
				   "in inode #%lu", blk, inode->i_ino);
			return -EIO;
		}
	}
	return 0;
}