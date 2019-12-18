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
typedef  int /*<<< orphan*/  u_int32_t ;
struct necp_session {int dummy; } ;
typedef  int /*<<< orphan*/  kern_ctl_ref ;
typedef  int /*<<< orphan*/  errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  necp_delete_session (struct necp_session*) ; 
 int /*<<< orphan*/  necp_policy_apply_all (struct necp_session*) ; 
 int /*<<< orphan*/  necp_policy_mark_all_for_deletion (struct necp_session*) ; 

__attribute__((used)) static errno_t
necp_ctl_disconnect(kern_ctl_ref kctlref, u_int32_t unit, void *unitinfo)
{
#pragma unused(kctlref, unit)
	struct necp_session *session = (struct necp_session *)unitinfo;
	if (session != NULL) {
		necp_policy_mark_all_for_deletion(session);
		necp_policy_apply_all(session);
		necp_delete_session((struct necp_session *)unitinfo);
	}

	return (0);
}