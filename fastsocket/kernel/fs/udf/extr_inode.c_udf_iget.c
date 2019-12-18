#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct kernel_lb_addr {scalar_t__ logicalBlockNum; size_t partitionReferenceNum; } ;
struct inode {int i_state; } ;
struct TYPE_6__ {int /*<<< orphan*/  i_location; } ;
struct TYPE_5__ {TYPE_1__* s_partmaps; } ;
struct TYPE_4__ {scalar_t__ s_partition_len; } ;

/* Variables and functions */
 int I_NEW ; 
 TYPE_3__* UDF_I (struct inode*) ; 
 TYPE_2__* UDF_SB (struct super_block*) ; 
 int /*<<< orphan*/  __udf_read_inode (struct inode*) ; 
 struct inode* iget_locked (struct super_block*,unsigned long) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 scalar_t__ is_bad_inode (struct inode*) ; 
 int /*<<< orphan*/  make_bad_inode (struct inode*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct kernel_lb_addr*,int) ; 
 int /*<<< orphan*/  udf_debug (char*,scalar_t__,size_t) ; 
 unsigned long udf_get_lb_pblock (struct super_block*,struct kernel_lb_addr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_new_inode (struct inode*) ; 

struct inode *udf_iget(struct super_block *sb, struct kernel_lb_addr *ino)
{
	unsigned long block = udf_get_lb_pblock(sb, ino, 0);
	struct inode *inode = iget_locked(sb, block);

	if (!inode)
		return NULL;

	if (inode->i_state & I_NEW) {
		memcpy(&UDF_I(inode)->i_location, ino, sizeof(struct kernel_lb_addr));
		__udf_read_inode(inode);
		unlock_new_inode(inode);
	}

	if (is_bad_inode(inode))
		goto out_iput;

	if (ino->logicalBlockNum >= UDF_SB(sb)->
			s_partmaps[ino->partitionReferenceNum].s_partition_len) {
		udf_debug("block=%d, partition=%d out of range\n",
			  ino->logicalBlockNum, ino->partitionReferenceNum);
		make_bad_inode(inode);
		goto out_iput;
	}

	return inode;

 out_iput:
	iput(inode);
	return NULL;
}