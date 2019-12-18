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
struct group_info {int dummy; } ;
struct cred {struct group_info* group_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_group_info (struct group_info*) ; 
 int /*<<< orphan*/  groups_sort (struct group_info*) ; 
 int /*<<< orphan*/  put_group_info (struct group_info*) ; 
 int security_task_setgroups (struct group_info*) ; 

int set_groups(struct cred *new, struct group_info *group_info)
{
	int retval;

	retval = security_task_setgroups(group_info);
	if (retval)
		return retval;

	put_group_info(new->group_info);
	groups_sort(group_info);
	get_group_info(group_info);
	new->group_info = group_info;
	return 0;
}