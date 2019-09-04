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
struct necp_session_policy {int pending_deletion; } ;
struct necp_session {int dirty; } ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  NECPLOG0 (int /*<<< orphan*/ ,char*) ; 
 int TRUE ; 
 scalar_t__ necp_debug ; 

__attribute__((used)) static bool
necp_policy_mark_for_deletion(struct necp_session *session, struct necp_session_policy *policy)
{
	if (session == NULL || policy == NULL) {
		return (FALSE);
	}

	policy->pending_deletion = TRUE;
	session->dirty = TRUE;

	if (necp_debug) {
		NECPLOG0(LOG_DEBUG, "Marked NECP policy for removal");
	}
	return (TRUE);
}