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
struct TYPE_4__ {int sb_versionnum; } ;
typedef  TYPE_1__ xfs_sb_t ;

/* Variables and functions */
 int XFS_SB_VERSION_3 ; 
 scalar_t__ XFS_SB_VERSION_4 ; 
 int XFS_SB_VERSION_NLINKBIT ; 
 scalar_t__ XFS_SB_VERSION_NUM (TYPE_1__*) ; 

__attribute__((used)) static inline int xfs_sb_version_hasnlink(xfs_sb_t *sbp)
{
	return sbp->sb_versionnum == XFS_SB_VERSION_3 ||
		 (XFS_SB_VERSION_NUM(sbp) == XFS_SB_VERSION_4 &&
		  (sbp->sb_versionnum & XFS_SB_VERSION_NLINKBIT));
}