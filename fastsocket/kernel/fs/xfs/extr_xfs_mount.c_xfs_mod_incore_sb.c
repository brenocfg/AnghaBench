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
typedef  scalar_t__ xfs_sb_field_t ;
struct xfs_mount {int /*<<< orphan*/  m_sb_lock; } ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ XFS_SBS_FDBLOCKS ; 
 scalar_t__ XFS_SBS_ICOUNT ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int xfs_mod_incore_sb_unlocked (struct xfs_mount*,scalar_t__,int /*<<< orphan*/ ,int) ; 

int
xfs_mod_incore_sb(
	struct xfs_mount	*mp,
	xfs_sb_field_t		field,
	int64_t			delta,
	int			rsvd)
{
	int			status;

#ifdef HAVE_PERCPU_SB
	ASSERT(field < XFS_SBS_ICOUNT || field > XFS_SBS_FDBLOCKS);
#endif
	spin_lock(&mp->m_sb_lock);
	status = xfs_mod_incore_sb_unlocked(mp, field, delta, rsvd);
	spin_unlock(&mp->m_sb_lock);

	return status;
}