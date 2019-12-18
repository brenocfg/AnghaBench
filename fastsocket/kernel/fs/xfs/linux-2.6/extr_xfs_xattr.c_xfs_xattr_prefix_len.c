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
 int XFS_ATTR_ROOT ; 
 int XFS_ATTR_SECURE ; 

__attribute__((used)) static unsigned int xfs_xattr_prefix_len(int flags)
{
	if (flags & XFS_ATTR_SECURE)
		return sizeof("security");
	else if (flags & XFS_ATTR_ROOT)
		return sizeof("trusted");
	else
		return sizeof("user");
}