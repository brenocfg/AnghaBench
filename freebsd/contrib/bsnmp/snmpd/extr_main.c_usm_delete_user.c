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
 int /*<<< orphan*/  SLIST_REMOVE (int /*<<< orphan*/ *,struct usm_user*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct usm_user*) ; 
 int /*<<< orphan*/  up ; 
 int /*<<< orphan*/  usm_user ; 
 int /*<<< orphan*/  usm_userlist ; 

void
usm_delete_user(struct usm_user *uuser)
{
	SLIST_REMOVE(&usm_userlist, uuser, usm_user, up);
	free(uuser);
}