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
struct TYPE_3__ {int /*<<< orphan*/  sb_versionnum; int /*<<< orphan*/  sb_features2; } ;
typedef  TYPE_1__ xfs_sb_t ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_SB_VERSION2_ATTR2BIT ; 
 int /*<<< orphan*/  XFS_SB_VERSION_MOREBITSBIT ; 

__attribute__((used)) static inline void xfs_sb_version_removeattr2(xfs_sb_t *sbp)
{
	sbp->sb_features2 &= ~XFS_SB_VERSION2_ATTR2BIT;
	if (!sbp->sb_features2)
		sbp->sb_versionnum &= ~XFS_SB_VERSION_MOREBITSBIT;
}