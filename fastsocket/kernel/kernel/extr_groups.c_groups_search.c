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
struct group_info {unsigned int ngroups; } ;
typedef  scalar_t__ gid_t ;

/* Variables and functions */
 scalar_t__ GROUP_AT (struct group_info const*,unsigned int) ; 

int groups_search(const struct group_info *group_info, gid_t grp)
{
	unsigned int left, right;

	if (!group_info)
		return 0;

	left = 0;
	right = group_info->ngroups;
	while (left < right) {
		unsigned int mid = (left+right)/2;
		if (grp > GROUP_AT(group_info, mid))
			left = mid + 1;
		else if (grp < GROUP_AT(group_info, mid))
			right = mid;
		else
			return 1;
	}
	return 0;
}