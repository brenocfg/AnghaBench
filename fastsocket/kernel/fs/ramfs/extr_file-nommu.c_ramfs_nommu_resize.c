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
typedef  int loff_t ;

/* Variables and functions */
 int EFBIG ; 
 int ramfs_nommu_check_mappings (struct inode*,int,int) ; 
 int ramfs_nommu_expand_for_mapping (struct inode*,int) ; 
 scalar_t__ unlikely (int) ; 
 int vmtruncate (struct inode*,int) ; 

__attribute__((used)) static int ramfs_nommu_resize(struct inode *inode, loff_t newsize, loff_t size)
{
	int ret;

	/* assume a truncate from zero size is going to be for the purposes of
	 * shared mmap */
	if (size == 0) {
		if (unlikely(newsize >> 32))
			return -EFBIG;

		return ramfs_nommu_expand_for_mapping(inode, newsize);
	}

	/* check that a decrease in size doesn't cut off any shared mappings */
	if (newsize < size) {
		ret = ramfs_nommu_check_mappings(inode, newsize, size);
		if (ret < 0)
			return ret;
	}

	ret = vmtruncate(inode, newsize);

	return ret;
}