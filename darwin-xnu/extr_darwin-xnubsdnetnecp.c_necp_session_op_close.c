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
typedef  int /*<<< orphan*/  vfs_context_t ;
struct necp_session {int dummy; } ;
struct fileglob {int /*<<< orphan*/ * fg_data; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  necp_delete_session (struct necp_session*) ; 
 int /*<<< orphan*/  necp_policy_apply_all (struct necp_session*) ; 
 int /*<<< orphan*/  necp_policy_mark_all_for_deletion (struct necp_session*) ; 

__attribute__((used)) static int
necp_session_op_close(struct fileglob *fg, vfs_context_t ctx)
{
#pragma unused(ctx)
	struct necp_session *session = (struct necp_session *)fg->fg_data;
	fg->fg_data = NULL;

	if (session != NULL) {
		necp_policy_mark_all_for_deletion(session);
		necp_policy_apply_all(session);
		necp_delete_session(session);
		return (0);
	} else {
		return (ENOENT);
	}
}