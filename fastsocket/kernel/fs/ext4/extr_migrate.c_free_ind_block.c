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
typedef  int /*<<< orphan*/  handle_t ;
typedef  scalar_t__ __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  EXT4_FREE_BLOCKS_METADATA ; 
 int /*<<< orphan*/  ext4_free_blocks (int /*<<< orphan*/ *,struct inode*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  extend_credit_for_blkdel (int /*<<< orphan*/ *,struct inode*) ; 
 int free_dind_blocks (int /*<<< orphan*/ *,struct inode*,scalar_t__) ; 
 int free_tind_blocks (int /*<<< orphan*/ *,struct inode*,scalar_t__) ; 
 int /*<<< orphan*/  le32_to_cpu (scalar_t__) ; 

__attribute__((used)) static int free_ind_block(handle_t *handle, struct inode *inode, __le32 *i_data)
{
	int retval;

	/* ei->i_data[EXT4_IND_BLOCK] */
	if (i_data[0]) {
		extend_credit_for_blkdel(handle, inode);
		ext4_free_blocks(handle, inode,
				le32_to_cpu(i_data[0]), 1,
				EXT4_FREE_BLOCKS_METADATA);
	}

	/* ei->i_data[EXT4_DIND_BLOCK] */
	if (i_data[1]) {
		retval = free_dind_blocks(handle, inode, i_data[1]);
		if (retval)
			return retval;
	}

	/* ei->i_data[EXT4_TIND_BLOCK] */
	if (i_data[2]) {
		retval = free_tind_blocks(handle, inode, i_data[2]);
		if (retval)
			return retval;
	}
	return 0;
}