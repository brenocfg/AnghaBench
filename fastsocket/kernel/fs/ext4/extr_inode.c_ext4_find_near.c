#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct inode {int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_mode; } ;
struct ext4_inode_info {int i_block_group; scalar_t__* i_data; } ;
typedef  int ext4_grpblk_t ;
typedef  int ext4_group_t ;
typedef  scalar_t__ ext4_fsblk_t ;
typedef  scalar_t__ __le32 ;
struct TYPE_10__ {int pid; } ;
struct TYPE_9__ {int /*<<< orphan*/  s_es; } ;
struct TYPE_8__ {TYPE_1__* bh; scalar_t__* p; } ;
struct TYPE_7__ {scalar_t__ b_blocknr; scalar_t__ b_data; } ;
typedef  TYPE_2__ Indirect ;

/* Variables and functions */
 int /*<<< orphan*/  DELALLOC ; 
 int EXT4_BLOCKS_PER_GROUP (int /*<<< orphan*/ ) ; 
 int EXT4_FLEX_SIZE_DIR_ALLOC_SCHEME ; 
 struct ext4_inode_info* EXT4_I (struct inode*) ; 
 TYPE_3__* EXT4_SB (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 TYPE_5__* current ; 
 scalar_t__ ext4_blocks_count (int /*<<< orphan*/ ) ; 
 int ext4_flex_bg_size (TYPE_3__*) ; 
 scalar_t__ ext4_group_first_block_no (int /*<<< orphan*/ ,int) ; 
 scalar_t__ le32_to_cpu (scalar_t__) ; 
 scalar_t__ test_opt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ext4_fsblk_t ext4_find_near(struct inode *inode, Indirect *ind)
{
	struct ext4_inode_info *ei = EXT4_I(inode);
	__le32 *start = ind->bh ? (__le32 *) ind->bh->b_data : ei->i_data;
	__le32 *p;
	ext4_fsblk_t bg_start;
	ext4_fsblk_t last_block;
	ext4_grpblk_t colour;
	ext4_group_t block_group;
	int flex_size = ext4_flex_bg_size(EXT4_SB(inode->i_sb));

	/* Try to find previous block */
	for (p = ind->p - 1; p >= start; p--) {
		if (*p)
			return le32_to_cpu(*p);
	}

	/* No such thing, so let's try location of indirect block */
	if (ind->bh)
		return ind->bh->b_blocknr;

	/*
	 * It is going to be referred to from the inode itself? OK, just put it
	 * into the same cylinder group then.
	 */
	block_group = ei->i_block_group;
	if (flex_size >= EXT4_FLEX_SIZE_DIR_ALLOC_SCHEME) {
		block_group &= ~(flex_size-1);
		if (S_ISREG(inode->i_mode))
			block_group++;
	}
	bg_start = ext4_group_first_block_no(inode->i_sb, block_group);
	last_block = ext4_blocks_count(EXT4_SB(inode->i_sb)->s_es) - 1;

	/*
	 * If we are doing delayed allocation, we don't need take
	 * colour into account.
	 */
	if (test_opt(inode->i_sb, DELALLOC))
		return bg_start;

	if (bg_start + EXT4_BLOCKS_PER_GROUP(inode->i_sb) <= last_block)
		colour = (current->pid % 16) *
			(EXT4_BLOCKS_PER_GROUP(inode->i_sb) / 16);
	else
		colour = (current->pid % 16) * ((last_block - bg_start) / 16);
	return bg_start + colour;
}