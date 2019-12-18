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
struct vacm_user {int dummy; } ;

/* Variables and functions */
 struct vacm_user* SLIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vacm_userlist ; 

struct vacm_user *
vacm_first_user(void)
{
	return (SLIST_FIRST(&vacm_userlist));
}