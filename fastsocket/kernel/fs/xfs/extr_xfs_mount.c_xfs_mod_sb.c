#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* t_mountp; } ;
typedef  TYPE_1__ xfs_trans_t ;
typedef  int /*<<< orphan*/  xfs_sb_t ;
typedef  long long xfs_sb_field_t ;
struct TYPE_9__ {int /*<<< orphan*/  m_sb; } ;
typedef  TYPE_2__ xfs_mount_t ;
typedef  int /*<<< orphan*/  xfs_buf_t ;
typedef  int /*<<< orphan*/  __uint64_t ;
typedef  long long __int64_t ;
struct TYPE_10__ {int offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (long long) ; 
 int /*<<< orphan*/  XFS_BUF_TO_SBP (int /*<<< orphan*/ *) ; 
 long long XFS_SB_MOD_BITS ; 
 scalar_t__ xfs_highbit64 (int /*<<< orphan*/ ) ; 
 scalar_t__ xfs_lowbit64 (int /*<<< orphan*/ ) ; 
 TYPE_6__* xfs_sb_info ; 
 int /*<<< orphan*/  xfs_sb_to_disk (int /*<<< orphan*/ ,int /*<<< orphan*/ *,long long) ; 
 int /*<<< orphan*/ * xfs_trans_getsb (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_trans_log_buf (TYPE_1__*,int /*<<< orphan*/ *,int,int) ; 

void
xfs_mod_sb(xfs_trans_t *tp, __int64_t fields)
{
	xfs_buf_t	*bp;
	int		first;
	int		last;
	xfs_mount_t	*mp;
	xfs_sb_field_t	f;

	ASSERT(fields);
	if (!fields)
		return;
	mp = tp->t_mountp;
	bp = xfs_trans_getsb(tp, mp, 0);
	first = sizeof(xfs_sb_t);
	last = 0;

	/* translate/copy */

	xfs_sb_to_disk(XFS_BUF_TO_SBP(bp), &mp->m_sb, fields);

	/* find modified range */
	f = (xfs_sb_field_t)xfs_highbit64((__uint64_t)fields);
	ASSERT((1LL << f) & XFS_SB_MOD_BITS);
	last = xfs_sb_info[f + 1].offset - 1;

	f = (xfs_sb_field_t)xfs_lowbit64((__uint64_t)fields);
	ASSERT((1LL << f) & XFS_SB_MOD_BITS);
	first = xfs_sb_info[f].offset;

	xfs_trans_log_buf(tp, bp, first, last);
}