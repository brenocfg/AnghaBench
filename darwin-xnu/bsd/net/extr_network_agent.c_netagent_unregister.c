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
struct netagent_session {int dummy; } ;
typedef  scalar_t__ netagent_session_t ;
typedef  int /*<<< orphan*/  errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  NETAGENTLOG0 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netagent_unregister_session_wrapper (struct netagent_session*) ; 

errno_t
netagent_unregister(netagent_session_t _session)
{
	struct netagent_session *session = (struct netagent_session *)_session;
	if (session == NULL) {
		NETAGENTLOG0(LOG_ERR, "Cannot unregister NULL session");
		return EINVAL;
	}

	netagent_unregister_session_wrapper(session);
	return 0;
}