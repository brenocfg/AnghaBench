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
typedef  int /*<<< orphan*/  gid_t ;

/* Variables and functions */
 int NGROUPS_MAX ; 
 scalar_t__ getgrouplist (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int setgroups (int,int /*<<< orphan*/ *) ; 

int initgroups(const char *user, gid_t gid)
{
	gid_t groups[NGROUPS_MAX];
	int count = NGROUPS_MAX;
	if (getgrouplist(user, gid, groups, &count) < 0) return -1;
	return setgroups(count, groups);
}