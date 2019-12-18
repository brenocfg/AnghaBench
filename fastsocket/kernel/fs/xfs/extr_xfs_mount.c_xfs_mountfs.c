#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_55__   TYPE_4__ ;
typedef  struct TYPE_54__   TYPE_3__ ;
typedef  struct TYPE_53__   TYPE_2__ ;
typedef  struct TYPE_52__   TYPE_1__ ;

/* Type definitions */
struct TYPE_53__ {int sb_blocksize; int sb_qflags; int /*<<< orphan*/  sb_rootino; int /*<<< orphan*/  sb_agcount; int /*<<< orphan*/  sb_inprogress; int /*<<< orphan*/  sb_logblocks; int /*<<< orphan*/  sb_logstart; int /*<<< orphan*/  sb_uuid; int /*<<< orphan*/  sb_blocklog; int /*<<< orphan*/  sb_features2; int /*<<< orphan*/  sb_bad_features2; } ;
typedef  TYPE_2__ xfs_sb_t ;
struct TYPE_54__ {int m_update_flags; int m_flags; int m_attr_magicpct; scalar_t__ m_logdev_targp; scalar_t__ m_qflags; scalar_t__ m_ddev_targp; TYPE_2__ m_sb; TYPE_4__* m_rootip; int /*<<< orphan*/  m_maxagi; int /*<<< orphan*/  m_perag_tree; int /*<<< orphan*/  m_perag_lock; scalar_t__ m_dmevmask; int /*<<< orphan*/  m_fixedfsid; int /*<<< orphan*/  m_inode_cluster_size; int /*<<< orphan*/  m_maxioffset; } ;
typedef  TYPE_3__ xfs_mount_t ;
struct TYPE_52__ {int di_mode; } ;
struct TYPE_55__ {scalar_t__ i_ino; TYPE_1__ i_d; } ;
typedef  TYPE_4__ xfs_inode_t ;
typedef  scalar_t__ uint ;
typedef  int /*<<< orphan*/  __uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  EFSCORRUPTED ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_RADIX_TREE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRELE (TYPE_4__*) ; 
 int S_IFDIR ; 
 int S_IFMT ; 
 int XFS_ALL_QUOTA_ACCT ; 
 int /*<<< orphan*/  XFS_ATTR_FORK ; 
 int /*<<< orphan*/  XFS_DATA_FORK ; 
 int /*<<< orphan*/  XFS_ERRLEVEL_LOW ; 
 int XFS_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFS_ERROR_REPORT (char*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  XFS_FSB_TO_BB (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFS_FSB_TO_DADDR (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFS_ILOCK_EXCL ; 
 int /*<<< orphan*/  XFS_INODE_BIG_CLUSTER_SIZE ; 
 int /*<<< orphan*/  XFS_IS_QUOTA_ON (TYPE_3__*) ; 
 scalar_t__ XFS_IS_QUOTA_RUNNING (TYPE_3__*) ; 
 int /*<<< orphan*/  XFS_LAST_UNMOUNT_WAS_CLEAN (TYPE_3__*) ; 
 int XFS_MOUNT_ATTR2 ; 
 int XFS_MOUNT_NOATTR2 ; 
 int XFS_MOUNT_RDONLY ; 
 int XFS_SB_BAD_FEATURES2 ; 
 int XFS_SB_FEATURES2 ; 
 int XFS_SB_VERSIONNUM ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  uuid_getnodeuniq (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_alloc_compute_maxlevels (TYPE_3__*) ; 
 int /*<<< orphan*/  xfs_bmap_compute_maxlevels (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int xfs_check_sizes (TYPE_3__*) ; 
 int /*<<< orphan*/  xfs_default_resblks (TYPE_3__*) ; 
 int /*<<< orphan*/  xfs_dir_mount (TYPE_3__*) ; 
 int /*<<< orphan*/  xfs_free_perag (TYPE_3__*) ; 
 int /*<<< orphan*/  xfs_ialloc_compute_maxlevels (TYPE_3__*) ; 
 int xfs_iget (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__**) ; 
 int xfs_initialize_perag (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int xfs_initialize_perag_data (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_iunlock (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int xfs_log_mount (TYPE_3__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int xfs_log_mount_finish (TYPE_3__*) ; 
 int /*<<< orphan*/  xfs_log_unmount (TYPE_3__*) ; 
 int /*<<< orphan*/  xfs_max_file_offset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_mount_common (TYPE_3__*,TYPE_2__*) ; 
 int xfs_mount_log_sb (TYPE_3__*,int) ; 
 int xfs_mount_reset_sbqflags (TYPE_3__*) ; 
 int /*<<< orphan*/  xfs_notice (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  xfs_qm_mount_quotas (TYPE_3__*) ; 
 int xfs_qm_newmount (TYPE_3__*,scalar_t__*,scalar_t__*) ; 
 int xfs_reserve_blocks (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int xfs_rtmount_init (TYPE_3__*) ; 
 int xfs_rtmount_inodes (TYPE_3__*) ; 
 int /*<<< orphan*/  xfs_rtunmount_inodes (TYPE_3__*) ; 
 scalar_t__ xfs_sb_has_mismatched_features2 (TYPE_2__*) ; 
 scalar_t__ xfs_sb_version_hasattr2 (TYPE_2__*) ; 
 scalar_t__ xfs_sb_version_haslazysbcount (TYPE_2__*) ; 
 int /*<<< orphan*/  xfs_sb_version_removeattr2 (TYPE_2__*) ; 
 int /*<<< orphan*/  xfs_set_inoalignment (TYPE_3__*) ; 
 int /*<<< orphan*/  xfs_set_low_space_thresholds (TYPE_3__*) ; 
 int /*<<< orphan*/  xfs_set_maxicount (TYPE_3__*) ; 
 int /*<<< orphan*/  xfs_set_rw_sizes (TYPE_3__*) ; 
 int /*<<< orphan*/  xfs_trans_init (TYPE_3__*) ; 
 int xfs_update_alignment (TYPE_3__*) ; 
 int xfs_uuid_mount (TYPE_3__*) ; 
 int /*<<< orphan*/  xfs_uuid_unmount (TYPE_3__*) ; 
 int /*<<< orphan*/  xfs_wait_buftarg (scalar_t__) ; 
 int /*<<< orphan*/  xfs_warn (TYPE_3__*,char*,...) ; 

int
xfs_mountfs(
	xfs_mount_t	*mp)
{
	xfs_sb_t	*sbp = &(mp->m_sb);
	xfs_inode_t	*rip;
	__uint64_t	resblks;
	uint		quotamount = 0;
	uint		quotaflags = 0;
	int		error = 0;

	xfs_mount_common(mp, sbp);

	/*
	 * Check for a mismatched features2 values.  Older kernels
	 * read & wrote into the wrong sb offset for sb_features2
	 * on some platforms due to xfs_sb_t not being 64bit size aligned
	 * when sb_features2 was added, which made older superblock
	 * reading/writing routines swap it as a 64-bit value.
	 *
	 * For backwards compatibility, we make both slots equal.
	 *
	 * If we detect a mismatched field, we OR the set bits into the
	 * existing features2 field in case it has already been modified; we
	 * don't want to lose any features.  We then update the bad location
	 * with the ORed value so that older kernels will see any features2
	 * flags, and mark the two fields as needing updates once the
	 * transaction subsystem is online.
	 */
	if (xfs_sb_has_mismatched_features2(sbp)) {
		xfs_warn(mp, "correcting sb_features alignment problem");
		sbp->sb_features2 |= sbp->sb_bad_features2;
		sbp->sb_bad_features2 = sbp->sb_features2;
		mp->m_update_flags |= XFS_SB_FEATURES2 | XFS_SB_BAD_FEATURES2;

		/*
		 * Re-check for ATTR2 in case it was found in bad_features2
		 * slot.
		 */
		if (xfs_sb_version_hasattr2(&mp->m_sb) &&
		   !(mp->m_flags & XFS_MOUNT_NOATTR2))
			mp->m_flags |= XFS_MOUNT_ATTR2;
	}

	if (xfs_sb_version_hasattr2(&mp->m_sb) &&
	   (mp->m_flags & XFS_MOUNT_NOATTR2)) {
		xfs_sb_version_removeattr2(&mp->m_sb);
		mp->m_update_flags |= XFS_SB_FEATURES2;

		/* update sb_versionnum for the clearing of the morebits */
		if (!sbp->sb_features2)
			mp->m_update_flags |= XFS_SB_VERSIONNUM;
	}

	/*
	 * Check if sb_agblocks is aligned at stripe boundary
	 * If sb_agblocks is NOT aligned turn off m_dalign since
	 * allocator alignment is within an ag, therefore ag has
	 * to be aligned at stripe boundary.
	 */
	error = xfs_update_alignment(mp);
	if (error)
		goto out;

	xfs_alloc_compute_maxlevels(mp);
	xfs_bmap_compute_maxlevels(mp, XFS_DATA_FORK);
	xfs_bmap_compute_maxlevels(mp, XFS_ATTR_FORK);
	xfs_ialloc_compute_maxlevels(mp);

	xfs_set_maxicount(mp);

	mp->m_maxioffset = xfs_max_file_offset(sbp->sb_blocklog);

	error = xfs_uuid_mount(mp);
	if (error)
		goto out;

	/*
	 * Set the minimum read and write sizes
	 */
	xfs_set_rw_sizes(mp);

	/* set the low space thresholds for dynamic preallocation */
	xfs_set_low_space_thresholds(mp);

	/*
	 * Set the inode cluster size.
	 * This may still be overridden by the file system
	 * block size if it is larger than the chosen cluster size.
	 */
	mp->m_inode_cluster_size = XFS_INODE_BIG_CLUSTER_SIZE;

	/*
	 * Set inode alignment fields
	 */
	xfs_set_inoalignment(mp);

	/*
	 * Check that the data (and log if separate) are an ok size.
	 */
	error = xfs_check_sizes(mp);
	if (error)
		goto out_remove_uuid;

	/*
	 * Initialize realtime fields in the mount structure
	 */
	error = xfs_rtmount_init(mp);
	if (error) {
		xfs_warn(mp, "RT mount failed");
		goto out_remove_uuid;
	}

	/*
	 *  Copies the low order bits of the timestamp and the randomly
	 *  set "sequence" number out of a UUID.
	 */
	uuid_getnodeuniq(&sbp->sb_uuid, mp->m_fixedfsid);

	mp->m_dmevmask = 0;	/* not persistent; set after each mount */

	xfs_dir_mount(mp);

	/*
	 * Initialize the attribute manager's entries.
	 */
	mp->m_attr_magicpct = (mp->m_sb.sb_blocksize * 37) / 100;

	/*
	 * Initialize the precomputed transaction reservations values.
	 */
	xfs_trans_init(mp);

	/*
	 * Allocate and initialize the per-ag data.
	 */
	spin_lock_init(&mp->m_perag_lock);
	INIT_RADIX_TREE(&mp->m_perag_tree, GFP_ATOMIC);
	error = xfs_initialize_perag(mp, sbp->sb_agcount, &mp->m_maxagi);
	if (error) {
		xfs_warn(mp, "Failed per-ag init: %d", error);
		goto out_remove_uuid;
	}

	if (!sbp->sb_logblocks) {
		xfs_warn(mp, "no log defined");
		XFS_ERROR_REPORT("xfs_mountfs", XFS_ERRLEVEL_LOW, mp);
		error = XFS_ERROR(EFSCORRUPTED);
		goto out_free_perag;
	}

	/*
	 * log's mount-time initialization. Perform 1st part recovery if needed
	 */
	error = xfs_log_mount(mp, mp->m_logdev_targp,
			      XFS_FSB_TO_DADDR(mp, sbp->sb_logstart),
			      XFS_FSB_TO_BB(mp, sbp->sb_logblocks));
	if (error) {
		xfs_warn(mp, "log mount failed");
		goto out_fail_wait;
	}

	/*
	 * Now the log is mounted, we know if it was an unclean shutdown or
	 * not. If it was, with the first phase of recovery has completed, we
	 * have consistent AG blocks on disk. We have not recovered EFIs yet,
	 * but they are recovered transactionally in the second recovery phase
	 * later.
	 *
	 * Hence we can safely re-initialise incore superblock counters from
	 * the per-ag data. These may not be correct if the filesystem was not
	 * cleanly unmounted, so we need to wait for recovery to finish before
	 * doing this.
	 *
	 * If the filesystem was cleanly unmounted, then we can trust the
	 * values in the superblock to be correct and we don't need to do
	 * anything here.
	 *
	 * If we are currently making the filesystem, the initialisation will
	 * fail as the perag data is in an undefined state.
	 */
	if (xfs_sb_version_haslazysbcount(&mp->m_sb) &&
	    !XFS_LAST_UNMOUNT_WAS_CLEAN(mp) &&
	     !mp->m_sb.sb_inprogress) {
		error = xfs_initialize_perag_data(mp, sbp->sb_agcount);
		if (error)
			goto out_fail_wait;
	}

	/*
	 * Get and sanity-check the root inode.
	 * Save the pointer to it in the mount structure.
	 */
	error = xfs_iget(mp, NULL, sbp->sb_rootino, 0, XFS_ILOCK_EXCL, &rip);
	if (error) {
		xfs_warn(mp, "failed to read root inode");
		goto out_log_dealloc;
	}

	ASSERT(rip != NULL);

	if (unlikely((rip->i_d.di_mode & S_IFMT) != S_IFDIR)) {
		xfs_warn(mp, "corrupted root inode %llu: not a directory",
			(unsigned long long)rip->i_ino);
		xfs_iunlock(rip, XFS_ILOCK_EXCL);
		XFS_ERROR_REPORT("xfs_mountfs_int(2)", XFS_ERRLEVEL_LOW,
				 mp);
		error = XFS_ERROR(EFSCORRUPTED);
		goto out_rele_rip;
	}
	mp->m_rootip = rip;	/* save it */

	xfs_iunlock(rip, XFS_ILOCK_EXCL);

	/*
	 * Initialize realtime inode pointers in the mount structure
	 */
	error = xfs_rtmount_inodes(mp);
	if (error) {
		/*
		 * Free up the root inode.
		 */
		xfs_warn(mp, "failed to read RT inodes");
		goto out_rele_rip;
	}

	/*
	 * If this is a read-only mount defer the superblock updates until
	 * the next remount into writeable mode.  Otherwise we would never
	 * perform the update e.g. for the root filesystem.
	 */
	if (mp->m_update_flags && !(mp->m_flags & XFS_MOUNT_RDONLY)) {
		error = xfs_mount_log_sb(mp, mp->m_update_flags);
		if (error) {
			xfs_warn(mp, "failed to write sb changes");
			goto out_rtunmount;
		}
	}

	/*
	 * Initialise the XFS quota management subsystem for this mount
	 */
	if (XFS_IS_QUOTA_RUNNING(mp)) {
		error = xfs_qm_newmount(mp, &quotamount, &quotaflags);
		if (error)
			goto out_rtunmount;
	} else {
		ASSERT(!XFS_IS_QUOTA_ON(mp));

		/*
		 * If a file system had quotas running earlier, but decided to
		 * mount without -o uquota/pquota/gquota options, revoke the
		 * quotachecked license.
		 */
		if (mp->m_sb.sb_qflags & XFS_ALL_QUOTA_ACCT) {
			xfs_notice(mp, "resetting quota flags");
			error = xfs_mount_reset_sbqflags(mp);
			if (error)
				return error;
		}
	}

	/*
	 * Finish recovering the file system.  This part needed to be
	 * delayed until after the root and real-time bitmap inodes
	 * were consistently read in.
	 */
	error = xfs_log_mount_finish(mp);
	if (error) {
		xfs_warn(mp, "log mount finish failed");
		goto out_rtunmount;
	}

	/*
	 * Complete the quota initialisation, post-log-replay component.
	 */
	if (quotamount) {
		ASSERT(mp->m_qflags == 0);
		mp->m_qflags = quotaflags;

		xfs_qm_mount_quotas(mp);
	}

	/*
	 * Now we are mounted, reserve a small amount of unused space for
	 * privileged transactions. This is needed so that transaction
	 * space required for critical operations can dip into this pool
	 * when at ENOSPC. This is needed for operations like create with
	 * attr, unwritten extent conversion at ENOSPC, etc. Data allocations
	 * are not allowed to use this reserved space.
	 *
	 * This may drive us straight to ENOSPC on mount, but that implies
	 * we were already there on the last unmount. Warn if this occurs.
	 */
	if (!(mp->m_flags & XFS_MOUNT_RDONLY)) {
		resblks = xfs_default_resblks(mp);
		error = xfs_reserve_blocks(mp, &resblks, NULL);
		if (error)
			xfs_warn(mp,
	"Unable to allocate reserve blocks. Continuing without reserve pool.");
	}

	return 0;

 out_rtunmount:
	xfs_rtunmount_inodes(mp);
 out_rele_rip:
	IRELE(rip);
 out_log_dealloc:
	xfs_log_unmount(mp);
 out_fail_wait:
	if (mp->m_logdev_targp && mp->m_logdev_targp != mp->m_ddev_targp)
		xfs_wait_buftarg(mp->m_logdev_targp);
	xfs_wait_buftarg(mp->m_ddev_targp);
 out_free_perag:
	xfs_free_perag(mp);
 out_remove_uuid:
	xfs_uuid_unmount(mp);
 out:
	return error;
}