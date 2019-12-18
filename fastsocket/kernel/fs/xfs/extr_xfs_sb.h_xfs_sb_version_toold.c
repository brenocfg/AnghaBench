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

/* Variables and functions */
 int XFS_SB_VERSION_1 ; 
 int XFS_SB_VERSION_2 ; 
 int XFS_SB_VERSION_3 ; 
 unsigned int XFS_SB_VERSION_ALIGNBIT ; 
 unsigned int XFS_SB_VERSION_ATTRBIT ; 
 unsigned int XFS_SB_VERSION_NLINKBIT ; 
 unsigned int XFS_SB_VERSION_QUOTABIT ; 

__attribute__((used)) static inline unsigned xfs_sb_version_toold(unsigned v)
{
	if (v & (XFS_SB_VERSION_QUOTABIT | XFS_SB_VERSION_ALIGNBIT))
		return 0;
	if (v & XFS_SB_VERSION_NLINKBIT)
		return XFS_SB_VERSION_3;
	if (v & XFS_SB_VERSION_ATTRBIT)
		return XFS_SB_VERSION_2;
	return XFS_SB_VERSION_1;
}