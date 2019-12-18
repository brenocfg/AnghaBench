#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ allocated; } ;
struct TYPE_7__ {TYPE_1__ b; } ;
struct TYPE_8__ {int bc_nlevels; scalar_t__ bc_btnum; TYPE_2__ bc_private; scalar_t__* bc_bufs; int /*<<< orphan*/  bc_tp; } ;
typedef  TYPE_3__ xfs_btree_cur_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ XFS_BTNUM_BMAP ; 
 int /*<<< orphan*/  kmem_zone_free (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  xfs_btree_cur_zone ; 
 int /*<<< orphan*/  xfs_trans_brelse (int /*<<< orphan*/ ,scalar_t__) ; 

void
xfs_btree_del_cursor(
	xfs_btree_cur_t	*cur,		/* btree cursor */
	int		error)		/* del because of error */
{
	int		i;		/* btree level */

	/*
	 * Clear the buffer pointers, and release the buffers.
	 * If we're doing this in the face of an error, we
	 * need to make sure to inspect all of the entries
	 * in the bc_bufs array for buffers to be unlocked.
	 * This is because some of the btree code works from
	 * level n down to 0, and if we get an error along
	 * the way we won't have initialized all the entries
	 * down to 0.
	 */
	for (i = 0; i < cur->bc_nlevels; i++) {
		if (cur->bc_bufs[i])
			xfs_trans_brelse(cur->bc_tp, cur->bc_bufs[i]);
		else if (!error)
			break;
	}
	/*
	 * Can't free a bmap cursor without having dealt with the
	 * allocated indirect blocks' accounting.
	 */
	ASSERT(cur->bc_btnum != XFS_BTNUM_BMAP ||
	       cur->bc_private.b.allocated == 0);
	/*
	 * Free the cursor.
	 */
	kmem_zone_free(xfs_btree_cur_zone, cur);
}