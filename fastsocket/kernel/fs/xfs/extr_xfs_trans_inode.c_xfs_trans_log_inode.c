#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  t_flags; } ;
typedef  TYPE_4__ xfs_trans_t ;
struct TYPE_13__ {TYPE_3__* i_itemp; TYPE_4__* i_transp; } ;
typedef  TYPE_5__ xfs_inode_t ;
typedef  int /*<<< orphan*/  uint ;
struct TYPE_9__ {TYPE_2__* li_desc; } ;
struct TYPE_11__ {int /*<<< orphan*/  ili_fields; int /*<<< orphan*/  ili_last_fields; TYPE_1__ ili_item; } ;
struct TYPE_10__ {int /*<<< orphan*/  lid_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  XFS_ILOCK_EXCL ; 
 int /*<<< orphan*/  XFS_LID_DIRTY ; 
 int /*<<< orphan*/  XFS_TRANS_DIRTY ; 
 int xfs_isilocked (TYPE_5__*,int /*<<< orphan*/ ) ; 

void
xfs_trans_log_inode(
	xfs_trans_t	*tp,
	xfs_inode_t	*ip,
	uint		flags)
{
	ASSERT(ip->i_transp == tp);
	ASSERT(ip->i_itemp != NULL);
	ASSERT(xfs_isilocked(ip, XFS_ILOCK_EXCL));

	tp->t_flags |= XFS_TRANS_DIRTY;
	ip->i_itemp->ili_item.li_desc->lid_flags |= XFS_LID_DIRTY;

	/*
	 * Always OR in the bits from the ili_last_fields field.
	 * This is to coordinate with the xfs_iflush() and xfs_iflush_done()
	 * routines in the eventual clearing of the ili_fields bits.
	 * See the big comment in xfs_iflush() for an explanation of
	 * this coordination mechanism.
	 */
	flags |= ip->i_itemp->ili_last_fields;
	ip->i_itemp->ili_fields |= flags;
}