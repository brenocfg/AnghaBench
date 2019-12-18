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
struct usm_user {int dummy; } ;

/* Variables and functions */
 struct usm_user* SLIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLIST_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct usm_user*) ; 
 int /*<<< orphan*/  up ; 
 int /*<<< orphan*/  usm_userlist ; 

void
usm_flush_users(void)
{
	struct usm_user *uuser;

	while ((uuser = SLIST_FIRST(&usm_userlist)) != NULL) {
		SLIST_REMOVE_HEAD(&usm_userlist, up);
		free(uuser);
	}

	SLIST_INIT(&usm_userlist);
}