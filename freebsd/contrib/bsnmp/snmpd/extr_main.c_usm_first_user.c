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
 int /*<<< orphan*/  usm_userlist ; 

struct usm_user *
usm_first_user(void)
{
	return (SLIST_FIRST(&usm_userlist));
}