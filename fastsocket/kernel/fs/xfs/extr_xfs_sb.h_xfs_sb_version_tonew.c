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
 unsigned int XFS_SB_VERSION_1 ; 
 unsigned int XFS_SB_VERSION_2 ; 
 int XFS_SB_VERSION_4 ; 
 int XFS_SB_VERSION_ATTRBIT ; 
 int XFS_SB_VERSION_NLINKBIT ; 

__attribute__((used)) static inline unsigned xfs_sb_version_tonew(unsigned v)
{
	if (v == XFS_SB_VERSION_1)
		return XFS_SB_VERSION_4;

	if (v == XFS_SB_VERSION_2)
		return XFS_SB_VERSION_4 | XFS_SB_VERSION_ATTRBIT;

	return XFS_SB_VERSION_4 | XFS_SB_VERSION_ATTRBIT |
		XFS_SB_VERSION_NLINKBIT;
}