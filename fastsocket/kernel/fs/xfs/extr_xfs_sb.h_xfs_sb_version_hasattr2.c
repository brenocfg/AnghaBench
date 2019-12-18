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
struct TYPE_4__ {int sb_features2; } ;
typedef  TYPE_1__ xfs_sb_t ;

/* Variables and functions */
 int XFS_SB_VERSION2_ATTR2BIT ; 
 scalar_t__ xfs_sb_version_hasmorebits (TYPE_1__*) ; 

__attribute__((used)) static inline int xfs_sb_version_hasattr2(xfs_sb_t *sbp)
{
	return xfs_sb_version_hasmorebits(sbp) &&
		(sbp->sb_features2 & XFS_SB_VERSION2_ATTR2BIT);
}