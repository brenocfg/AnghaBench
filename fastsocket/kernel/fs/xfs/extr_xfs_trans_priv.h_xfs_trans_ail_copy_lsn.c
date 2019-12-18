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
typedef  int /*<<< orphan*/  xfs_lsn_t ;
struct xfs_ail {int /*<<< orphan*/  xa_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
xfs_trans_ail_copy_lsn(
	struct xfs_ail	*ailp,
	xfs_lsn_t	*dst,
	xfs_lsn_t	*src)
{
	ASSERT(sizeof(xfs_lsn_t) == 8);	/* don't lock if it shrinks */
	spin_lock(&ailp->xa_lock);
	*dst = *src;
	spin_unlock(&ailp->xa_lock);
}