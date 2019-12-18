#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_11__ ;
typedef  struct TYPE_17__   TYPE_10__ ;

/* Type definitions */
struct TYPE_20__ {int zs_mirrors; int zs_splits; } ;
typedef  TYPE_2__ ztest_shared_t ;
typedef  int /*<<< orphan*/  ztest_ds_t ;
struct TYPE_21__ {scalar_t__ vdev_resilver_txg; int vdev_guid; int /*<<< orphan*/  vdev_path; void* vdev_cant_write; void* vdev_cant_read; scalar_t__ vdev_id; TYPE_4__* vdev_tsd; TYPE_11__* vdev_top; } ;
typedef  TYPE_3__ vdev_t ;
typedef  int /*<<< orphan*/  vdev_label_t ;
struct TYPE_22__ {TYPE_1__* vf_vnode; } ;
typedef  TYPE_4__ vdev_file_t ;
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  u_longlong_t ;
struct TYPE_24__ {unsigned long long sav_count; TYPE_3__** sav_vdevs; } ;
struct TYPE_23__ {TYPE_6__ spa_l2cache; int /*<<< orphan*/  spa_root_vdev; } ;
typedef  TYPE_5__ spa_t ;
typedef  TYPE_6__ spa_aux_vdev_t ;
typedef  int /*<<< orphan*/  pathrand ;
typedef  int /*<<< orphan*/  path0 ;
typedef  void* boolean_t ;
typedef  int /*<<< orphan*/  bad ;
struct TYPE_19__ {int v_fd; } ;
struct TYPE_18__ {scalar_t__ vdev_islog; } ;
struct TYPE_17__ {int zo_raidz; int zo_verbose; int /*<<< orphan*/  zo_pool; int /*<<< orphan*/  zo_dir; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 void* B_FALSE ; 
 void* B_TRUE ; 
 scalar_t__ EBUSY ; 
 int /*<<< orphan*/  FTAG ; 
 int INT_MAX ; 
 int MAX (int,int) ; 
 int MAXFAULTS () ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/  O_RDWR ; 
 int P2ALIGN (size_t,int) ; 
 int /*<<< orphan*/  RW_READER ; 
 int /*<<< orphan*/  RW_WRITER ; 
 int /*<<< orphan*/  SCL_STATE ; 
 int /*<<< orphan*/  SEEK_END ; 
 int SPA_MAXBLOCKSHIFT ; 
 int VDEV_LABEL_END_SIZE ; 
 int VDEV_LABEL_START_SIZE ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int ZFS_OFFLINE_TEMPORARY ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  fatal (int,char*,int,char*) ; 
 size_t lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*,int /*<<< orphan*/ ) ; 
 int pwrite (int,int*,int,int) ; 
 int /*<<< orphan*/  rw_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spa_config_enter (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_config_exit (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 TYPE_3__* vdev_lookup_by_path (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ vdev_offline (TYPE_5__*,int,int) ; 
 int /*<<< orphan*/  vdev_online (TYPE_5__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vdev_resilver_needed (TYPE_11__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_dbgmsg (char*,long long,int) ; 
 char* ztest_dev_template ; 
 scalar_t__ ztest_device_removal_active ; 
 int /*<<< orphan*/  ztest_name_lock ; 
 TYPE_10__ ztest_opts ; 
 unsigned long long ztest_random (unsigned long long) ; 
 int ztest_random_vdev_top (TYPE_5__*,void*) ; 
 TYPE_2__* ztest_shared ; 
 TYPE_5__* ztest_spa ; 
 int /*<<< orphan*/  ztest_vdev_lock ; 

void
ztest_fault_inject(ztest_ds_t *zd, uint64_t id)
{
	ztest_shared_t *zs = ztest_shared;
	spa_t *spa = ztest_spa;
	int fd;
	uint64_t offset;
	uint64_t leaves;
	uint64_t bad = 0x1990c0ffeedecadeULL;
	uint64_t top, leaf;
	char path0[MAXPATHLEN];
	char pathrand[MAXPATHLEN];
	size_t fsize;
	int bshift = SPA_MAXBLOCKSHIFT + 2;
	int iters = 1000;
	int maxfaults;
	int mirror_save;
	vdev_t *vd0 = NULL;
	uint64_t guid0 = 0;
	boolean_t islog = B_FALSE;

	mutex_enter(&ztest_vdev_lock);

	/*
	 * Device removal is in progress, fault injection must be disabled
	 * until it completes and the pool is scrubbed.  The fault injection
	 * strategy for damaging blocks does not take in to account evacuated
	 * blocks which may have already been damaged.
	 */
	if (ztest_device_removal_active) {
		mutex_exit(&ztest_vdev_lock);
		return;
	}

	maxfaults = MAXFAULTS();
	leaves = MAX(zs->zs_mirrors, 1) * ztest_opts.zo_raidz;
	mirror_save = zs->zs_mirrors;
	mutex_exit(&ztest_vdev_lock);

	ASSERT(leaves >= 1);

	/*
	 * Grab the name lock as reader. There are some operations
	 * which don't like to have their vdevs changed while
	 * they are in progress (i.e. spa_change_guid). Those
	 * operations will have grabbed the name lock as writer.
	 */
	rw_enter(&ztest_name_lock, RW_READER);

	/*
	 * We need SCL_STATE here because we're going to look at vd0->vdev_tsd.
	 */
	spa_config_enter(spa, SCL_STATE, FTAG, RW_READER);

	if (ztest_random(2) == 0) {
		/*
		 * Inject errors on a normal data device or slog device.
		 */
		top = ztest_random_vdev_top(spa, B_TRUE);
		leaf = ztest_random(leaves) + zs->zs_splits;

		/*
		 * Generate paths to the first leaf in this top-level vdev,
		 * and to the random leaf we selected.  We'll induce transient
		 * write failures and random online/offline activity on leaf 0,
		 * and we'll write random garbage to the randomly chosen leaf.
		 */
		(void) snprintf(path0, sizeof (path0), ztest_dev_template,
		    ztest_opts.zo_dir, ztest_opts.zo_pool,
		    top * leaves + zs->zs_splits);
		(void) snprintf(pathrand, sizeof (pathrand), ztest_dev_template,
		    ztest_opts.zo_dir, ztest_opts.zo_pool,
		    top * leaves + leaf);

		vd0 = vdev_lookup_by_path(spa->spa_root_vdev, path0);
		if (vd0 != NULL && vd0->vdev_top->vdev_islog)
			islog = B_TRUE;

		/*
		 * If the top-level vdev needs to be resilvered
		 * then we only allow faults on the device that is
		 * resilvering.
		 */
		if (vd0 != NULL && maxfaults != 1 &&
		    (!vdev_resilver_needed(vd0->vdev_top, NULL, NULL) ||
		    vd0->vdev_resilver_txg != 0)) {
			/*
			 * Make vd0 explicitly claim to be unreadable,
			 * or unwriteable, or reach behind its back
			 * and close the underlying fd.  We can do this if
			 * maxfaults == 0 because we'll fail and reexecute,
			 * and we can do it if maxfaults >= 2 because we'll
			 * have enough redundancy.  If maxfaults == 1, the
			 * combination of this with injection of random data
			 * corruption below exceeds the pool's fault tolerance.
			 */
			vdev_file_t *vf = vd0->vdev_tsd;

			zfs_dbgmsg("injecting fault to vdev %llu; maxfaults=%d",
			    (long long)vd0->vdev_id, (int)maxfaults);

			if (vf != NULL && ztest_random(3) == 0) {
				(void) close(vf->vf_vnode->v_fd);
				vf->vf_vnode->v_fd = -1;
			} else if (ztest_random(2) == 0) {
				vd0->vdev_cant_read = B_TRUE;
			} else {
				vd0->vdev_cant_write = B_TRUE;
			}
			guid0 = vd0->vdev_guid;
		}
	} else {
		/*
		 * Inject errors on an l2cache device.
		 */
		spa_aux_vdev_t *sav = &spa->spa_l2cache;

		if (sav->sav_count == 0) {
			spa_config_exit(spa, SCL_STATE, FTAG);
			rw_exit(&ztest_name_lock);
			return;
		}
		vd0 = sav->sav_vdevs[ztest_random(sav->sav_count)];
		guid0 = vd0->vdev_guid;
		(void) strcpy(path0, vd0->vdev_path);
		(void) strcpy(pathrand, vd0->vdev_path);

		leaf = 0;
		leaves = 1;
		maxfaults = INT_MAX;	/* no limit on cache devices */
	}

	spa_config_exit(spa, SCL_STATE, FTAG);
	rw_exit(&ztest_name_lock);

	/*
	 * If we can tolerate two or more faults, or we're dealing
	 * with a slog, randomly online/offline vd0.
	 */
	if ((maxfaults >= 2 || islog) && guid0 != 0) {
		if (ztest_random(10) < 6) {
			int flags = (ztest_random(2) == 0 ?
			    ZFS_OFFLINE_TEMPORARY : 0);

			/*
			 * We have to grab the zs_name_lock as writer to
			 * prevent a race between offlining a slog and
			 * destroying a dataset. Offlining the slog will
			 * grab a reference on the dataset which may cause
			 * dmu_objset_destroy() to fail with EBUSY thus
			 * leaving the dataset in an inconsistent state.
			 */
			if (islog)
				rw_enter(&ztest_name_lock, RW_WRITER);

			VERIFY(vdev_offline(spa, guid0, flags) != EBUSY);

			if (islog)
				rw_exit(&ztest_name_lock);
		} else {
			/*
			 * Ideally we would like to be able to randomly
			 * call vdev_[on|off]line without holding locks
			 * to force unpredictable failures but the side
			 * effects of vdev_[on|off]line prevent us from
			 * doing so. We grab the ztest_vdev_lock here to
			 * prevent a race between injection testing and
			 * aux_vdev removal.
			 */
			mutex_enter(&ztest_vdev_lock);
			(void) vdev_online(spa, guid0, 0, NULL);
			mutex_exit(&ztest_vdev_lock);
		}
	}

	if (maxfaults == 0)
		return;

	/*
	 * We have at least single-fault tolerance, so inject data corruption.
	 */
	fd = open(pathrand, O_RDWR);

	if (fd == -1) /* we hit a gap in the device namespace */
		return;

	fsize = lseek(fd, 0, SEEK_END);

	while (--iters != 0) {
		/*
		 * The offset must be chosen carefully to ensure that
		 * we do not inject a given logical block with errors
		 * on two different leaf devices, because ZFS can not
		 * tolerate that (if maxfaults==1).
		 *
		 * We divide each leaf into chunks of size
		 * (# leaves * SPA_MAXBLOCKSIZE * 4).  Within each chunk
		 * there is a series of ranges to which we can inject errors.
		 * Each range can accept errors on only a single leaf vdev.
		 * The error injection ranges are separated by ranges
		 * which we will not inject errors on any device (DMZs).
		 * Each DMZ must be large enough such that a single block
		 * can not straddle it, so that a single block can not be
		 * a target in two different injection ranges (on different
		 * leaf vdevs).
		 *
		 * For example, with 3 leaves, each chunk looks like:
		 *    0 to  32M: injection range for leaf 0
		 *  32M to  64M: DMZ - no injection allowed
		 *  64M to  96M: injection range for leaf 1
		 *  96M to 128M: DMZ - no injection allowed
		 * 128M to 160M: injection range for leaf 2
		 * 160M to 192M: DMZ - no injection allowed
		 */
		offset = ztest_random(fsize / (leaves << bshift)) *
		    (leaves << bshift) + (leaf << bshift) +
		    (ztest_random(1ULL << (bshift - 1)) & -8ULL);

		/*
		 * Only allow damage to the labels at one end of the vdev.
		 *
		 * If all labels are damaged, the device will be totally
		 * inaccessible, which will result in loss of data,
		 * because we also damage (parts of) the other side of
		 * the mirror/raidz.
		 *
		 * Additionally, we will always have both an even and an
		 * odd label, so that we can handle crashes in the
		 * middle of vdev_config_sync().
		 */
		if ((leaf & 1) == 0 && offset < VDEV_LABEL_START_SIZE)
			continue;

		/*
		 * The two end labels are stored at the "end" of the disk, but
		 * the end of the disk (vdev_psize) is aligned to
		 * sizeof (vdev_label_t).
		 */
		uint64_t psize = P2ALIGN(fsize, sizeof (vdev_label_t));
		if ((leaf & 1) == 1 &&
		    offset + sizeof (bad) > psize - VDEV_LABEL_END_SIZE)
			continue;

		mutex_enter(&ztest_vdev_lock);
		if (mirror_save != zs->zs_mirrors) {
			mutex_exit(&ztest_vdev_lock);
			(void) close(fd);
			return;
		}

		if (pwrite(fd, &bad, sizeof (bad), offset) != sizeof (bad))
			fatal(1, "can't inject bad word at 0x%llx in %s",
			    offset, pathrand);

		mutex_exit(&ztest_vdev_lock);

		if (ztest_opts.zo_verbose >= 7)
			(void) printf("injected bad word into %s,"
			    " offset 0x%llx\n", pathrand, (u_longlong_t)offset);
	}

	(void) close(fd);
}