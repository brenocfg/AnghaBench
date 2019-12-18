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
struct inode {int /*<<< orphan*/  i_mutex; int /*<<< orphan*/  i_alloc_sem; TYPE_1__* i_op; struct address_space* i_mapping; } ;
struct address_space {int dummy; } ;
typedef  scalar_t__ loff_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* truncate_range ) (struct inode*,scalar_t__,scalar_t__) ;} ;

/* Variables and functions */
 int ENOSYS ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ round_up (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct inode*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  unmap_mapping_range (struct address_space*,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int vmtruncate_range(struct inode *inode, loff_t lstart, loff_t lend)
{
	struct address_space *mapping = inode->i_mapping;
	loff_t holebegin = round_up(lstart, PAGE_SIZE);
	loff_t holelen = 1 + lend - holebegin;

	/*
	 * If the underlying filesystem is not going to provide
	 * a way to truncate a range of blocks (punch a hole) -
	 * we should return failure right now.
	 */
	if (!inode->i_op->truncate_range)
		return -ENOSYS;

	mutex_lock(&inode->i_mutex);
	down_write(&inode->i_alloc_sem);
	unmap_mapping_range(mapping, holebegin, holelen, 1);
	inode->i_op->truncate_range(inode, lstart, lend);
	/* unmap again to remove racily COWed private pages */
	unmap_mapping_range(mapping, holebegin, holelen, 1);
	up_write(&inode->i_alloc_sem);
	mutex_unlock(&inode->i_mutex);

	return 0;
}