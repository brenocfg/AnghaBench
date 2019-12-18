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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct ocfs2_dinode {int /*<<< orphan*/  i_suballoc_bit; int /*<<< orphan*/  i_blkno; } ;
struct inode {int dummy; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int ocfs2_free_suballoc_bits (int /*<<< orphan*/ *,struct inode*,struct buffer_head*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ocfs2_which_suballoc_group (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ocfs2_free_dinode(handle_t *handle,
		      struct inode *inode_alloc_inode,
		      struct buffer_head *inode_alloc_bh,
		      struct ocfs2_dinode *di)
{
	u64 blk = le64_to_cpu(di->i_blkno);
	u16 bit = le16_to_cpu(di->i_suballoc_bit);
	u64 bg_blkno = ocfs2_which_suballoc_group(blk, bit);

	return ocfs2_free_suballoc_bits(handle, inode_alloc_inode,
					inode_alloc_bh, bit, bg_blkno, 1);
}