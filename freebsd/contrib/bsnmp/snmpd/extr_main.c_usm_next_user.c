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
 struct usm_user* SLIST_NEXT (struct usm_user*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up ; 

struct usm_user *
usm_next_user(struct usm_user *uuser)
{
	if (uuser == NULL)
		return (NULL);

	return (SLIST_NEXT(uuser, up));
}