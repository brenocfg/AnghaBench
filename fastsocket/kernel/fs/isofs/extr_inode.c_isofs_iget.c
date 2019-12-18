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
struct super_block {int s_blocksize_bits; } ;
struct isofs_iget5_callback_data {unsigned long block; unsigned long offset; } ;
struct inode {int i_state; } ;

/* Variables and functions */
 long EINVAL ; 
 long ENOMEM ; 
 struct inode* ERR_PTR (long) ; 
 int I_NEW ; 
 struct inode* iget5_locked (struct super_block*,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct isofs_iget5_callback_data*) ; 
 int /*<<< orphan*/  iget_failed (struct inode*) ; 
 int /*<<< orphan*/  isofs_iget5_set ; 
 int /*<<< orphan*/  isofs_iget5_test ; 
 long isofs_read_inode (struct inode*) ; 
 int /*<<< orphan*/  unlock_new_inode (struct inode*) ; 

struct inode *isofs_iget(struct super_block *sb,
			 unsigned long block,
			 unsigned long offset)
{
	unsigned long hashval;
	struct inode *inode;
	struct isofs_iget5_callback_data data;
	long ret;

	if (offset >= 1ul << sb->s_blocksize_bits)
		return ERR_PTR(-EINVAL);

	data.block = block;
	data.offset = offset;

	hashval = (block << sb->s_blocksize_bits) | offset;

	inode = iget5_locked(sb, hashval, &isofs_iget5_test,
				&isofs_iget5_set, &data);

	if (!inode)
		return ERR_PTR(-ENOMEM);

	if (inode->i_state & I_NEW) {
		ret = isofs_read_inode(inode);
		if (ret < 0) {
			iget_failed(inode);
			inode = ERR_PTR(ret);
		} else {
			unlock_new_inode(inode);
		}
	}

	return inode;
}