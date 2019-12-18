#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * i_data; } ;
struct udf_inode_info {TYPE_2__ i_ext; } ;
struct inode {TYPE_1__* i_sb; } ;
struct TYPE_3__ {int s_flags; } ;

/* Variables and functions */
 int MS_RDONLY ; 
 struct udf_inode_info* UDF_I (struct inode*) ; 
 int /*<<< orphan*/  invalidate_inode_buffers (struct inode*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  udf_truncate_tail_extent (struct inode*) ; 
 int /*<<< orphan*/  unlock_kernel () ; 
 int /*<<< orphan*/  write_inode_now (struct inode*,int /*<<< orphan*/ ) ; 

void udf_clear_inode(struct inode *inode)
{
	struct udf_inode_info *iinfo;
	if (!(inode->i_sb->s_flags & MS_RDONLY)) {
		lock_kernel();
		udf_truncate_tail_extent(inode);
		unlock_kernel();
		write_inode_now(inode, 0);
		invalidate_inode_buffers(inode);
	}
	iinfo = UDF_I(inode);
	kfree(iinfo->i_ext.i_data);
	iinfo->i_ext.i_data = NULL;
}