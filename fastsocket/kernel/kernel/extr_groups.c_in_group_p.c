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
struct cred {scalar_t__ fsgid; int /*<<< orphan*/  group_info; } ;
typedef  scalar_t__ gid_t ;

/* Variables and functions */
 struct cred* current_cred () ; 
 int groups_search (int /*<<< orphan*/ ,scalar_t__) ; 

int in_group_p(gid_t grp)
{
	const struct cred *cred = current_cred();
	int retval = 1;

	if (grp != cred->fsgid)
		retval = groups_search(cred->group_info, grp);
	return retval;
}