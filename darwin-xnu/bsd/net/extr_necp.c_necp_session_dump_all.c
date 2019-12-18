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
struct necp_session_action_args {scalar_t__ out_buffer_length; scalar_t__ out_buffer; } ;
struct necp_session {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  NECPLOG (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int necp_handle_policy_dump_all (struct necp_session*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
necp_session_dump_all(struct necp_session *session, struct necp_session_action_args *uap, int *retval)
{
	int error = 0;

	if (uap->out_buffer_length == 0 || uap->out_buffer == 0) {
		NECPLOG(LOG_ERR, "necp_session_dump_all invalid output buffer (%zu)", uap->out_buffer_length);
		error = EINVAL;
		goto done;
	}

	error = necp_handle_policy_dump_all(session, 0, NULL, uap->out_buffer, uap->out_buffer_length, 0);
done:
	*retval = error;
	return (error);
}