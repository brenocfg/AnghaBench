#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct inode {TYPE_1__* i_sb; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  handle_t ;
typedef  scalar_t__ __le32 ;
struct TYPE_2__ {int s_blocksize; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  EXT4_FREE_BLOCKS_METADATA ; 
 int /*<<< orphan*/  ext4_free_blocks (int /*<<< orphan*/ *,struct inode*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  extend_credit_for_blkdel (int /*<<< orphan*/ *,struct inode*) ; 
 int free_dind_blocks (int /*<<< orphan*/ *,struct inode*,scalar_t__) ; 
 int /*<<< orphan*/  le32_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  put_bh (struct buffer_head*) ; 
 struct buffer_head* sb_bread (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int free_tind_blocks(handle_t *handle,
				struct inode *inode, __le32 i_data)
{
	int i, retval = 0;
	__le32 *tmp_idata;
	struct buffer_head *bh;
	unsigned long max_entries = inode->i_sb->s_blocksize >> 2;

	bh = sb_bread(inode->i_sb, le32_to_cpu(i_data));
	if (!bh)
		return -EIO;

	tmp_idata = (__le32 *)bh->b_data;
	for (i = 0; i < max_entries; i++) {
		if (tmp_idata[i]) {
			retval = free_dind_blocks(handle,
					inode, tmp_idata[i]);
			if (retval) {
				put_bh(bh);
				return retval;
			}
		}
	}
	put_bh(bh);
	extend_credit_for_blkdel(handle, inode);
	ext4_free_blocks(handle, inode, le32_to_cpu(i_data), 1,
			 EXT4_FREE_BLOCKS_METADATA);
	return 0;
}