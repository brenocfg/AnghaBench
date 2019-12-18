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
struct xfs_btree_cur {int bc_flags; } ;

/* Variables and functions */
 size_t XFS_BTREE_LBLOCK_LEN ; 
 int XFS_BTREE_LONG_PTRS ; 
 size_t XFS_BTREE_SBLOCK_LEN ; 

__attribute__((used)) static inline size_t xfs_btree_block_len(struct xfs_btree_cur *cur)
{
	return (cur->bc_flags & XFS_BTREE_LONG_PTRS) ?
		XFS_BTREE_LBLOCK_LEN :
		XFS_BTREE_SBLOCK_LEN;
}