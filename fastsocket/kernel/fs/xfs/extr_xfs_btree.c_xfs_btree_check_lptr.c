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
typedef  scalar_t__ xfs_dfsbno_t ;
struct xfs_btree_cur {int /*<<< orphan*/  bc_mp; } ;

/* Variables and functions */
 scalar_t__ NULLDFSBNO ; 
 scalar_t__ XFS_FSB_SANITY_CHECK (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  XFS_WANT_CORRUPTED_RETURN (int) ; 

int					/* error (0 or EFSCORRUPTED) */
xfs_btree_check_lptr(
	struct xfs_btree_cur	*cur,	/* btree cursor */
	xfs_dfsbno_t		bno,	/* btree block disk address */
	int			level)	/* btree block level */
{
	XFS_WANT_CORRUPTED_RETURN(
		level > 0 &&
		bno != NULLDFSBNO &&
		XFS_FSB_SANITY_CHECK(cur->bc_mp, bno));
	return 0;
}