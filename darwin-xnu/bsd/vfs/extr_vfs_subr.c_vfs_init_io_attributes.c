#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vnode_t ;
typedef  int /*<<< orphan*/ * vfs_context_t ;
typedef  int u_int64_t ;
typedef  int u_int32_t ;
typedef  void* u_int16_t ;
typedef  int off_t ;
typedef  TYPE_1__* mount_t ;
typedef  int errno_t ;
struct TYPE_5__ {int flags; } ;
typedef  TYPE_2__ dk_corestorage_info_t ;
typedef  scalar_t__ dk_apfs_flavour_t ;
typedef  int /*<<< orphan*/  caddr_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_4__ {scalar_t__ mnt_devbsdunit; int mnt_devblocksize; int mnt_maxreadcnt; int mnt_maxwritecnt; int mnt_maxsegreadsize; int mnt_maxsegwritesize; int mnt_alignmentmask; int mnt_ioqueue_depth; int mnt_ioscale; int mnt_ioflags; int mnt_minsaturationbytecount; void* mnt_segwritecnt; void* mnt_segreadcnt; int /*<<< orphan*/  mnt_kern_flag; int /*<<< orphan*/  mnt_throttle_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  DKIOCCORESTORAGE ; 
 int /*<<< orphan*/  DKIOCGETAPFSFLAVOUR ; 
 int /*<<< orphan*/  DKIOCGETBLOCKSIZE ; 
 int /*<<< orphan*/  DKIOCGETCOMMANDPOOLSIZE ; 
 int /*<<< orphan*/  DKIOCGETFEATURES ; 
 int /*<<< orphan*/  DKIOCGETIOMINSATURATIONBYTECOUNT ; 
 int /*<<< orphan*/  DKIOCGETMAXBLOCKCOUNTREAD ; 
 int /*<<< orphan*/  DKIOCGETMAXBLOCKCOUNTWRITE ; 
 int /*<<< orphan*/  DKIOCGETMAXBYTECOUNTREAD ; 
 int /*<<< orphan*/  DKIOCGETMAXBYTECOUNTWRITE ; 
 int /*<<< orphan*/  DKIOCGETMAXSEGMENTBYTECOUNTREAD ; 
 int /*<<< orphan*/  DKIOCGETMAXSEGMENTBYTECOUNTWRITE ; 
 int /*<<< orphan*/  DKIOCGETMAXSEGMENTCOUNTREAD ; 
 int /*<<< orphan*/  DKIOCGETMAXSEGMENTCOUNTWRITE ; 
 int /*<<< orphan*/  DKIOCGETMINSEGMENTALIGNMENTBYTECOUNT ; 
 int /*<<< orphan*/  DKIOCGETTHROTTLEMASK ; 
 int /*<<< orphan*/  DKIOCISSOLIDSTATE ; 
 int /*<<< orphan*/  DKIOCISVIRTUAL ; 
 scalar_t__ DK_APFS_FUSION ; 
 int DK_CORESTORAGE_PIN_YOUR_METADATA ; 
 int DK_FEATURE_FORCE_UNIT_ACCESS ; 
 int DK_FEATURE_PRIORITY ; 
 int DK_FEATURE_UNMAP ; 
 scalar_t__ FALSE ; 
 void* MAX_UPL_SIZE_BYTES ; 
 int /*<<< orphan*/  MNTK_ROOTDEV ; 
 int /*<<< orphan*/  MNTK_SSD ; 
 int /*<<< orphan*/  MNTK_VIRTUALDEV ; 
 int MNT_DEFAULT_IOQUEUE_DEPTH ; 
 int MNT_IOFLAGS_CSUNMAP_SUPPORTED ; 
 int MNT_IOFLAGS_FUA_SUPPORTED ; 
 int MNT_IOFLAGS_FUSION_DRIVE ; 
 int MNT_IOFLAGS_IOSCHED_SUPPORTED ; 
 int MNT_IOFLAGS_UNMAP_SUPPORTED ; 
 int MNT_IOSCALE (int) ; 
 int PAGE_MASK ; 
 int PAGE_SIZE ; 
 scalar_t__ TRUE ; 
 int UINT16_MAX ; 
 int UINT32_MAX ; 
 scalar_t__ VNOP_IOCTL (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ iosched_enabled ; 
 scalar_t__ num_trailing_0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 
 scalar_t__ rootunit ; 
 scalar_t__ rootvp ; 
 int /*<<< orphan*/  set_fsblocksize (scalar_t__) ; 
 int /*<<< orphan*/  throttle_info_disable_throttle (scalar_t__,int) ; 
 int /*<<< orphan*/ * vfs_context_current () ; 

errno_t
vfs_init_io_attributes(vnode_t devvp, mount_t mp)
{
	int	error;
	off_t	readblockcnt = 0;
	off_t	writeblockcnt = 0;
	off_t	readmaxcnt = 0;
	off_t	writemaxcnt = 0;
	off_t	readsegcnt = 0;
	off_t	writesegcnt = 0;
	off_t	readsegsize = 0;
	off_t	writesegsize = 0;
	off_t	alignment = 0;
	u_int32_t minsaturationbytecount = 0;
	u_int32_t ioqueue_depth = 0;
	u_int32_t blksize;
	u_int64_t temp;
	u_int32_t features;
	vfs_context_t ctx = vfs_context_current();
	dk_corestorage_info_t cs_info;
	boolean_t cs_present = FALSE;;
	int isssd = 0;
	int isvirtual = 0;


	VNOP_IOCTL(devvp, DKIOCGETTHROTTLEMASK, (caddr_t)&mp->mnt_throttle_mask, 0, NULL);
	/*
	 * as a reasonable approximation, only use the lowest bit of the mask
	 * to generate a disk unit number
	 */
	mp->mnt_devbsdunit = num_trailing_0(mp->mnt_throttle_mask);

	if (devvp == rootvp)
		rootunit = mp->mnt_devbsdunit;

	if (mp->mnt_devbsdunit == rootunit) {
		/*
		 * this mount point exists on the same device as the root
		 * partition, so it comes under the hard throttle control...
		 * this is true even for the root mount point itself
		 */
		mp->mnt_kern_flag |= MNTK_ROOTDEV;
	}
	/*
	 * force the spec device to re-cache
	 * the underlying block size in case
	 * the filesystem overrode the initial value
	 */
	set_fsblocksize(devvp);


	if ((error = VNOP_IOCTL(devvp, DKIOCGETBLOCKSIZE,
				(caddr_t)&blksize, 0, ctx)))
		return (error);

	mp->mnt_devblocksize = blksize;

	/*
	 * set the maximum possible I/O size
	 * this may get clipped to a smaller value
	 * based on which constraints are being advertised
	 * and if those advertised constraints result in a smaller
	 * limit for a given I/O
	 */
	mp->mnt_maxreadcnt = MAX_UPL_SIZE_BYTES;
	mp->mnt_maxwritecnt = MAX_UPL_SIZE_BYTES;

	if (VNOP_IOCTL(devvp, DKIOCISVIRTUAL, (caddr_t)&isvirtual, 0, ctx) == 0) {
	        if (isvirtual)
		        mp->mnt_kern_flag |= MNTK_VIRTUALDEV;
	}
	if (VNOP_IOCTL(devvp, DKIOCISSOLIDSTATE, (caddr_t)&isssd, 0, ctx) == 0) {
	        if (isssd)
		        mp->mnt_kern_flag |= MNTK_SSD;
	}
	if ((error = VNOP_IOCTL(devvp, DKIOCGETFEATURES,
				(caddr_t)&features, 0, ctx)))
		return (error);

	if ((error = VNOP_IOCTL(devvp, DKIOCGETMAXBLOCKCOUNTREAD,
				(caddr_t)&readblockcnt, 0, ctx)))
		return (error);

	if ((error = VNOP_IOCTL(devvp, DKIOCGETMAXBLOCKCOUNTWRITE,
				(caddr_t)&writeblockcnt, 0, ctx)))
		return (error);

	if ((error = VNOP_IOCTL(devvp, DKIOCGETMAXBYTECOUNTREAD,
				(caddr_t)&readmaxcnt, 0, ctx)))
		return (error);

	if ((error = VNOP_IOCTL(devvp, DKIOCGETMAXBYTECOUNTWRITE,
				(caddr_t)&writemaxcnt, 0, ctx)))
		return (error);

	if ((error = VNOP_IOCTL(devvp, DKIOCGETMAXSEGMENTCOUNTREAD,
				(caddr_t)&readsegcnt, 0, ctx)))
		return (error);

	if ((error = VNOP_IOCTL(devvp, DKIOCGETMAXSEGMENTCOUNTWRITE,
				(caddr_t)&writesegcnt, 0, ctx)))
		return (error);

	if ((error = VNOP_IOCTL(devvp, DKIOCGETMAXSEGMENTBYTECOUNTREAD,
				(caddr_t)&readsegsize, 0, ctx)))
		return (error);

	if ((error = VNOP_IOCTL(devvp, DKIOCGETMAXSEGMENTBYTECOUNTWRITE,
				(caddr_t)&writesegsize, 0, ctx)))
		return (error);

	if ((error = VNOP_IOCTL(devvp, DKIOCGETMINSEGMENTALIGNMENTBYTECOUNT,
				(caddr_t)&alignment, 0, ctx)))
		return (error);

	if ((error = VNOP_IOCTL(devvp, DKIOCGETCOMMANDPOOLSIZE,
				(caddr_t)&ioqueue_depth, 0, ctx)))
		return (error);

	if (readmaxcnt)
		mp->mnt_maxreadcnt = (readmaxcnt > UINT32_MAX) ? UINT32_MAX : readmaxcnt;

	if (readblockcnt) {
		temp = readblockcnt * blksize;
		temp = (temp > UINT32_MAX) ? UINT32_MAX : temp;

		if (temp < mp->mnt_maxreadcnt)
			mp->mnt_maxreadcnt = (u_int32_t)temp;
	}

	if (writemaxcnt)
		mp->mnt_maxwritecnt = (writemaxcnt > UINT32_MAX) ? UINT32_MAX : writemaxcnt;

	if (writeblockcnt) {
		temp = writeblockcnt * blksize;
		temp = (temp > UINT32_MAX) ? UINT32_MAX : temp;

		if (temp < mp->mnt_maxwritecnt)
			mp->mnt_maxwritecnt = (u_int32_t)temp;
	}

	if (readsegcnt) {
	        temp = (readsegcnt > UINT16_MAX) ? UINT16_MAX : readsegcnt;
	} else {
		temp = mp->mnt_maxreadcnt / PAGE_SIZE;

		if (temp > UINT16_MAX)
			temp = UINT16_MAX;
	}
	mp->mnt_segreadcnt = (u_int16_t)temp;

	if (writesegcnt) {
	        temp = (writesegcnt > UINT16_MAX) ? UINT16_MAX : writesegcnt;
	} else {
		temp = mp->mnt_maxwritecnt / PAGE_SIZE;

		if (temp > UINT16_MAX)
			temp = UINT16_MAX;
	}
	mp->mnt_segwritecnt = (u_int16_t)temp;

	if (readsegsize)
	        temp = (readsegsize > UINT32_MAX) ? UINT32_MAX : readsegsize;
	else
	        temp = mp->mnt_maxreadcnt;
	mp->mnt_maxsegreadsize = (u_int32_t)temp;

	if (writesegsize)
	        temp = (writesegsize > UINT32_MAX) ? UINT32_MAX : writesegsize;
	else
	        temp = mp->mnt_maxwritecnt;
	mp->mnt_maxsegwritesize = (u_int32_t)temp;

	if (alignment)
	        temp = (alignment > PAGE_SIZE) ? PAGE_MASK : alignment - 1;
	else
	        temp = 0;
	mp->mnt_alignmentmask = temp;


	if (ioqueue_depth > MNT_DEFAULT_IOQUEUE_DEPTH)
		temp = ioqueue_depth;
	else
		temp = MNT_DEFAULT_IOQUEUE_DEPTH;

	mp->mnt_ioqueue_depth = temp;
	mp->mnt_ioscale = MNT_IOSCALE(mp->mnt_ioqueue_depth);

	if (mp->mnt_ioscale > 1)
		printf("ioqueue_depth = %d,   ioscale = %d\n", (int)mp->mnt_ioqueue_depth, (int)mp->mnt_ioscale);

	if (features & DK_FEATURE_FORCE_UNIT_ACCESS)
	        mp->mnt_ioflags |= MNT_IOFLAGS_FUA_SUPPORTED;
	
	if (VNOP_IOCTL(devvp, DKIOCGETIOMINSATURATIONBYTECOUNT, (caddr_t)&minsaturationbytecount, 0, ctx) == 0) {
		mp->mnt_minsaturationbytecount = minsaturationbytecount;
	} else {
		mp->mnt_minsaturationbytecount = 0;
	}

	if (VNOP_IOCTL(devvp, DKIOCCORESTORAGE, (caddr_t)&cs_info, 0, ctx) == 0)
		cs_present = TRUE;

	if (features & DK_FEATURE_UNMAP) {
		mp->mnt_ioflags |= MNT_IOFLAGS_UNMAP_SUPPORTED;

		if (cs_present == TRUE)
			mp->mnt_ioflags |= MNT_IOFLAGS_CSUNMAP_SUPPORTED;
	}
	if (cs_present == TRUE) {
		/*
		 * for now we'll use the following test as a proxy for
		 * the underlying drive being FUSION in nature
		 */
		if ((cs_info.flags & DK_CORESTORAGE_PIN_YOUR_METADATA))
			mp->mnt_ioflags |= MNT_IOFLAGS_FUSION_DRIVE;
	} else {
		/* Check for APFS Fusion */
		dk_apfs_flavour_t flavour;
		if ((VNOP_IOCTL(devvp, DKIOCGETAPFSFLAVOUR, (caddr_t)&flavour, 0, ctx) == 0) &&
		    (flavour == DK_APFS_FUSION)) {
			mp->mnt_ioflags |= MNT_IOFLAGS_FUSION_DRIVE;
		}
	}

#if CONFIG_IOSCHED
        if (iosched_enabled && (features & DK_FEATURE_PRIORITY)) {
                mp->mnt_ioflags |= MNT_IOFLAGS_IOSCHED_SUPPORTED;
		throttle_info_disable_throttle(mp->mnt_devbsdunit, (mp->mnt_ioflags & MNT_IOFLAGS_FUSION_DRIVE) != 0);
	}
#endif /* CONFIG_IOSCHED */
	return (error);
}