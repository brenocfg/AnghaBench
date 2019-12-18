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
struct vacm_user {struct vacm_user* group; int /*<<< orphan*/  group_users; } ;

/* Variables and functions */
 scalar_t__ SLIST_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLIST_REMOVE (int /*<<< orphan*/ *,struct vacm_user*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct vacm_user*) ; 
 struct vacm_user vacm_default_group ; 
 int /*<<< orphan*/  vacm_group ; 
 int /*<<< orphan*/  vacm_grouplist ; 
 int /*<<< orphan*/  vacm_user ; 
 int /*<<< orphan*/  vacm_userlist ; 
 int /*<<< orphan*/  vge ; 
 int /*<<< orphan*/  vvg ; 
 int /*<<< orphan*/  vvu ; 

int
vacm_delete_user(struct vacm_user *user)
{
	if (user->group != NULL && user->group != &vacm_default_group) {
		SLIST_REMOVE(&user->group->group_users, user, vacm_user, vvg);
		if (SLIST_EMPTY(&user->group->group_users)) {
			SLIST_REMOVE(&vacm_grouplist, user->group,
			    vacm_group, vge);
			free(user->group);
		}
	}

	SLIST_REMOVE(&vacm_userlist, user, vacm_user, vvu);
	free(user);

	return (0);
}