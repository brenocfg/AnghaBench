#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ sb_fdblocks; } ;
struct TYPE_10__ {scalar_t__ m_resblks; scalar_t__ m_resblks_avail; int /*<<< orphan*/  m_sb_lock; TYPE_1__ m_sb; } ;
typedef  TYPE_2__ xfs_mount_t ;
struct TYPE_11__ {scalar_t__ resblks; scalar_t__ resblks_avail; } ;
typedef  TYPE_3__ xfs_fsop_resblks_t ;
typedef  scalar_t__ __uint64_t ;
typedef  scalar_t__ __int64_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOSPC ; 
 scalar_t__ XFS_ALLOC_SET_ASIDE (TYPE_2__*) ; 
 int /*<<< orphan*/  XFS_SBS_FDBLOCKS ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int xfs_icsb_modify_counters (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_icsb_sync_counters_locked (TYPE_2__*,int /*<<< orphan*/ ) ; 

int
xfs_reserve_blocks(
	xfs_mount_t             *mp,
	__uint64_t              *inval,
	xfs_fsop_resblks_t      *outval)
{
	__int64_t		lcounter, delta, fdblks_delta;
	__uint64_t		request;

	/* If inval is null, report current values and return */
	if (inval == (__uint64_t *)NULL) {
		if (!outval)
			return EINVAL;
		outval->resblks = mp->m_resblks;
		outval->resblks_avail = mp->m_resblks_avail;
		return 0;
	}

	request = *inval;

	/*
	 * With per-cpu counters, this becomes an interesting
	 * problem. we needto work out if we are freeing or allocation
	 * blocks first, then we can do the modification as necessary.
	 *
	 * We do this under the m_sb_lock so that if we are near
	 * ENOSPC, we will hold out any changes while we work out
	 * what to do. This means that the amount of free space can
	 * change while we do this, so we need to retry if we end up
	 * trying to reserve more space than is available.
	 *
	 * We also use the xfs_mod_incore_sb() interface so that we
	 * don't have to care about whether per cpu counter are
	 * enabled, disabled or even compiled in....
	 */
retry:
	spin_lock(&mp->m_sb_lock);
	xfs_icsb_sync_counters_locked(mp, 0);

	/*
	 * If our previous reservation was larger than the current value,
	 * then move any unused blocks back to the free pool.
	 */
	fdblks_delta = 0;
	if (mp->m_resblks > request) {
		lcounter = mp->m_resblks_avail - request;
		if (lcounter  > 0) {		/* release unused blocks */
			fdblks_delta = lcounter;
			mp->m_resblks_avail -= lcounter;
		}
		mp->m_resblks = request;
	} else {
		__int64_t	free;

		free =  mp->m_sb.sb_fdblocks - XFS_ALLOC_SET_ASIDE(mp);
		if (!free)
			goto out; /* ENOSPC and fdblks_delta = 0 */

		delta = request - mp->m_resblks;
		lcounter = free - delta;
		if (lcounter < 0) {
			/* We can't satisfy the request, just get what we can */
			mp->m_resblks += free;
			mp->m_resblks_avail += free;
			fdblks_delta = -free;
		} else {
			fdblks_delta = -delta;
			mp->m_resblks = request;
			mp->m_resblks_avail += delta;
		}
	}
out:
	if (outval) {
		outval->resblks = mp->m_resblks;
		outval->resblks_avail = mp->m_resblks_avail;
	}
	spin_unlock(&mp->m_sb_lock);

	if (fdblks_delta) {
		/*
		 * If we are putting blocks back here, m_resblks_avail is
		 * already at its max so this will put it in the free pool.
		 *
		 * If we need space, we'll either succeed in getting it
		 * from the free block count or we'll get an enospc. If
		 * we get a ENOSPC, it means things changed while we were
		 * calculating fdblks_delta and so we should try again to
		 * see if there is anything left to reserve.
		 *
		 * Don't set the reserved flag here - we don't want to reserve
		 * the extra reserve blocks from the reserve.....
		 */
		int error;
		error = xfs_icsb_modify_counters(mp, XFS_SBS_FDBLOCKS,
						 fdblks_delta, 0);
		if (error == ENOSPC)
			goto retry;
	}
	return 0;
}