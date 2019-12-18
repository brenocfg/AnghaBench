#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dtrace_optval_t ;
struct TYPE_7__ {int /*<<< orphan*/ * dt_options; } ;
typedef  TYPE_1__ dtrace_hdl_t ;
struct TYPE_8__ {size_t o_option; int /*<<< orphan*/ * o_name; } ;
typedef  TYPE_2__ dt_option_t ;

/* Variables and functions */
 int /*<<< orphan*/  EDT_BADOPTNAME ; 
 int /*<<< orphan*/  EINVAL ; 
 TYPE_2__* _dtrace_drtoptions ; 
 TYPE_2__* _dtrace_rtoptions ; 
 int dt_set_errno (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char const*) ; 

int
dtrace_getopt(dtrace_hdl_t *dtp, const char *opt, dtrace_optval_t *val)
{
	const dt_option_t *op;

	if (opt == NULL)
		return (dt_set_errno(dtp, EINVAL));

	/*
	 * We only need to search the run-time options -- it's not legal
	 * to get the values of compile-time options.
	 */
	for (op = _dtrace_rtoptions; op->o_name != NULL; op++) {
		if (strcmp(op->o_name, opt) == 0) {
			*val = dtp->dt_options[op->o_option];
			return (0);
		}
	}

	for (op = _dtrace_drtoptions; op->o_name != NULL; op++) {
		if (strcmp(op->o_name, opt) == 0) {
			*val = dtp->dt_options[op->o_option];
			return (0);
		}
	}

	return (dt_set_errno(dtp, EDT_BADOPTNAME));
}