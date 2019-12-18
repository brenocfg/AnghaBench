#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ dtrace_optval_t ;
struct TYPE_5__ {scalar_t__* dt_options; } ;
typedef  TYPE_1__ dtrace_hdl_t ;
struct TYPE_6__ {scalar_t__ dtbp_policy; int /*<<< orphan*/ * dtbp_name; } ;

/* Variables and functions */
 size_t DTRACEOPT_BUFPOLICY ; 
 scalar_t__ DTRACEOPT_UNSET ; 
 int /*<<< orphan*/  EDT_BADOPTVAL ; 
 TYPE_4__* _dtrace_bufpolicies ; 
 int dt_set_errno (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static int
dt_opt_bufpolicy(dtrace_hdl_t *dtp, const char *arg, uintptr_t option)
{
	dtrace_optval_t policy = DTRACEOPT_UNSET;
	int i;

	if (arg == NULL)
		return (dt_set_errno(dtp, EDT_BADOPTVAL));

	for (i = 0; _dtrace_bufpolicies[i].dtbp_name != NULL; i++) {
		if (strcmp(_dtrace_bufpolicies[i].dtbp_name, arg) == 0) {
			policy = _dtrace_bufpolicies[i].dtbp_policy;
			break;
		}
	}

	if (policy == DTRACEOPT_UNSET)
		return (dt_set_errno(dtp, EDT_BADOPTVAL));

	dtp->dt_options[DTRACEOPT_BUFPOLICY] = policy;

	return (0);
}