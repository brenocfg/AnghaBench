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
struct netagent_session {int dummy; } ;
typedef  int /*<<< orphan*/  kern_ctl_ref ;
typedef  int /*<<< orphan*/  errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOPROTOOPT ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  NETAGENTLOG0 (int /*<<< orphan*/ ,char*) ; 
#define  NETAGENT_OPTION_TYPE_USE_COUNT 128 
 int /*<<< orphan*/  netagent_handle_use_count_getopt (struct netagent_session*,void*,size_t*) ; 

__attribute__((used)) static errno_t
netagent_ctl_getopt(kern_ctl_ref kctlref, u_int32_t unit, void *unitinfo, int opt,
					void *data, size_t *len)
{
#pragma unused(kctlref, unit)
	struct netagent_session *session = (struct netagent_session *)unitinfo;
	errno_t error;

	if (session == NULL) {
		NETAGENTLOG0(LOG_ERR, "Received a NULL session");
		error = EINVAL;
		goto done;
	}

	switch (opt) {
		case NETAGENT_OPTION_TYPE_USE_COUNT: {
			NETAGENTLOG0(LOG_DEBUG, "Request to get use count");
			error = netagent_handle_use_count_getopt(session, data, len);
		}
		break;
		default:
			NETAGENTLOG0(LOG_ERR, "Received unknown option");
			error = ENOPROTOOPT;
		break;
	}

done:
	return (error);
}