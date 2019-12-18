#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ msb_field; int /*<<< orphan*/  msb_delta; } ;
typedef  TYPE_1__ xfs_mod_sb_t ;
typedef  int uint ;
struct xfs_mount {int /*<<< orphan*/  m_sb_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ XFS_SBS_FDBLOCKS ; 
 scalar_t__ XFS_SBS_ICOUNT ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int xfs_mod_incore_sb_unlocked (struct xfs_mount*,scalar_t__,int /*<<< orphan*/ ,int) ; 

int
xfs_mod_incore_sb_batch(
	struct xfs_mount	*mp,
	xfs_mod_sb_t		*msb,
	uint			nmsb,
	int			rsvd)
{
	xfs_mod_sb_t		*msbp;
	int			error = 0;

	/*
	 * Loop through the array of mod structures and apply each individually.
	 * If any fail, then back out all those which have already been applied.
	 * Do all of this within the scope of the m_sb_lock so that all of the
	 * changes will be atomic.
	 */
	spin_lock(&mp->m_sb_lock);
	for (msbp = msb; msbp < (msb + nmsb); msbp++) {
		ASSERT(msbp->msb_field < XFS_SBS_ICOUNT ||
		       msbp->msb_field > XFS_SBS_FDBLOCKS);

		error = xfs_mod_incore_sb_unlocked(mp, msbp->msb_field,
						   msbp->msb_delta, rsvd);
		if (error)
			goto unwind;
	}
	spin_unlock(&mp->m_sb_lock);
	return 0;

unwind:
	while (--msbp >= msb) {
		error = xfs_mod_incore_sb_unlocked(mp, msbp->msb_field,
						   -msbp->msb_delta, rsvd);
		ASSERT(error == 0);
	}
	spin_unlock(&mp->m_sb_lock);
	return error;
}