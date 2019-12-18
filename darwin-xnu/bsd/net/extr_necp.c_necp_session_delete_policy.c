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
struct necp_session_policy {scalar_t__ pending_deletion; } ;
struct necp_session_action_args {int in_buffer_length; scalar_t__ in_buffer; } ;
struct necp_session {int dummy; } ;
typedef  int necp_policy_id ;
typedef  int /*<<< orphan*/  delete_policy_id ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  NECPLOG (int /*<<< orphan*/ ,char*,int) ; 
 int copyin (scalar_t__,int*,int) ; 
 struct necp_session_policy* necp_policy_find (struct necp_session*,int) ; 
 int /*<<< orphan*/  necp_policy_mark_for_deletion (struct necp_session*,struct necp_session_policy*) ; 

__attribute__((used)) static int
necp_session_delete_policy(struct necp_session *session, struct necp_session_action_args *uap, int *retval)
{
	int error = 0;

	if (uap->in_buffer_length < sizeof(necp_policy_id) || uap->in_buffer == 0) {
		NECPLOG(LOG_ERR, "necp_session_delete_policy invalid input (%zu)", uap->in_buffer_length);
		error = EINVAL;
		goto done;
	}

	necp_policy_id delete_policy_id = 0;
	error = copyin(uap->in_buffer, &delete_policy_id, sizeof(delete_policy_id));
	if (error != 0) {
		NECPLOG(LOG_ERR, "necp_session_delete_policy policy_id copyin error (%d)", error);
		goto done;
	}

	struct necp_session_policy *policy = necp_policy_find(session, delete_policy_id);
	if (policy == NULL || policy->pending_deletion) {
		NECPLOG(LOG_ERR, "necp_session_delete_policy failed to find policy with id %u", delete_policy_id);
		error = ENOENT;
		goto done;
	}

	necp_policy_mark_for_deletion(session, policy);
done:
	*retval = error;
	return (error);
}