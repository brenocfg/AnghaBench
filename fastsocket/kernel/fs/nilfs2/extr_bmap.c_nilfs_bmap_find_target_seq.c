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
struct nilfs_bmap {scalar_t__ b_last_allocated_key; scalar_t__ b_last_allocated_ptr; } ;
typedef  scalar_t__ __u64 ;
typedef  scalar_t__ __s64 ;

/* Variables and functions */
 scalar_t__ NILFS_BMAP_INVALID_PTR ; 
 scalar_t__ NILFS_INODE_BMAP_SIZE ; 
 scalar_t__ nilfs_bmap_keydiff_abs (scalar_t__) ; 

__u64 nilfs_bmap_find_target_seq(const struct nilfs_bmap *bmap, __u64 key)
{
	__s64 diff;

	diff = key - bmap->b_last_allocated_key;
	if ((nilfs_bmap_keydiff_abs(diff) < NILFS_INODE_BMAP_SIZE) &&
	    (bmap->b_last_allocated_ptr != NILFS_BMAP_INVALID_PTR) &&
	    (bmap->b_last_allocated_ptr + diff > 0))
		return bmap->b_last_allocated_ptr + diff;
	else
		return NILFS_BMAP_INVALID_PTR;
}