#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int sb_versionnum; int sb_features2; scalar_t__ sb_shared_vn; } ;
typedef  TYPE_1__ xfs_sb_t ;

/* Variables and functions */
 scalar_t__ XFS_SB_MAX_SHARED_VN ; 
 int XFS_SB_VERSION2_OKREALBITS ; 
 int XFS_SB_VERSION_1 ; 
 int XFS_SB_VERSION_3 ; 
 scalar_t__ XFS_SB_VERSION_4 ; 
 int XFS_SB_VERSION_MOREBITSBIT ; 
 scalar_t__ XFS_SB_VERSION_NUM (TYPE_1__*) ; 
 int XFS_SB_VERSION_OKREALBITS ; 
 int XFS_SB_VERSION_SHAREDBIT ; 

__attribute__((used)) static inline int xfs_sb_good_version(xfs_sb_t *sbp)
{
	/* We always support version 1-3 */
	if (sbp->sb_versionnum >= XFS_SB_VERSION_1 &&
	    sbp->sb_versionnum <= XFS_SB_VERSION_3)
		return 1;

	/* We support version 4 if all feature bits are supported */
	if (XFS_SB_VERSION_NUM(sbp) == XFS_SB_VERSION_4) {
		if ((sbp->sb_versionnum & ~XFS_SB_VERSION_OKREALBITS) ||
		    ((sbp->sb_versionnum & XFS_SB_VERSION_MOREBITSBIT) &&
		     (sbp->sb_features2 & ~XFS_SB_VERSION2_OKREALBITS)))
			return 0;

#ifdef __KERNEL__
		if (sbp->sb_shared_vn > XFS_SB_MAX_SHARED_VN)
			return 0;
#else
		if ((sbp->sb_versionnum & XFS_SB_VERSION_SHAREDBIT) &&
		    sbp->sb_shared_vn > XFS_SB_MAX_SHARED_VN)
			return 0;
#endif

		return 1;
	}

	return 0;
}