#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ dt_active; } ;
typedef  TYPE_1__ dtrace_hdl_t ;
struct TYPE_12__ {int (* o_func ) (TYPE_1__*,char const*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  o_option; int /*<<< orphan*/ * o_name; } ;
typedef  TYPE_2__ dt_option_t ;

/* Variables and functions */
 int /*<<< orphan*/  EDT_ACTIVE ; 
 int /*<<< orphan*/  EDT_BADOPTNAME ; 
 int /*<<< orphan*/  EINVAL ; 
 TYPE_2__* _dtrace_ctoptions ; 
 TYPE_2__* _dtrace_drtoptions ; 
 TYPE_2__* _dtrace_rtoptions ; 
 int dt_set_errno (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char const*) ; 
 int stub1 (TYPE_1__*,char const*,int /*<<< orphan*/ ) ; 
 int stub2 (TYPE_1__*,char const*,int /*<<< orphan*/ ) ; 
 int stub3 (TYPE_1__*,char const*,int /*<<< orphan*/ ) ; 

int
dtrace_setopt(dtrace_hdl_t *dtp, const char *opt, const char *val)
{
	const dt_option_t *op;

	if (opt == NULL)
		return (dt_set_errno(dtp, EINVAL));

	for (op = _dtrace_ctoptions; op->o_name != NULL; op++) {
		if (strcmp(op->o_name, opt) == 0)
			return (op->o_func(dtp, val, op->o_option));
	}

	for (op = _dtrace_drtoptions; op->o_name != NULL; op++) {
		if (strcmp(op->o_name, opt) == 0)
			return (op->o_func(dtp, val, op->o_option));
	}

	for (op = _dtrace_rtoptions; op->o_name != NULL; op++) {
		if (strcmp(op->o_name, opt) == 0) {
			/*
			 * Only dynamic run-time options may be set while
			 * tracing is active.
			 */
			if (dtp->dt_active)
				return (dt_set_errno(dtp, EDT_ACTIVE));

			return (op->o_func(dtp, val, op->o_option));
		}
	}

	return (dt_set_errno(dtp, EDT_BADOPTNAME));
}