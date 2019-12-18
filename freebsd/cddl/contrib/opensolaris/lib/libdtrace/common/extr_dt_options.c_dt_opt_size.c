#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dtrace_optval_t ;
struct TYPE_4__ {int /*<<< orphan*/ * dt_options; } ;
typedef  TYPE_1__ dtrace_hdl_t ;

/* Variables and functions */
 int /*<<< orphan*/  EDT_BADOPTVAL ; 
 scalar_t__ dt_optval_parse (char const*,int /*<<< orphan*/ *) ; 
 int dt_set_errno (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dt_opt_size(dtrace_hdl_t *dtp, const char *arg, uintptr_t option)
{
	dtrace_optval_t val = 0;

	if (arg != NULL && dt_optval_parse(arg, &val) != 0)
		return (dt_set_errno(dtp, EDT_BADOPTVAL));

	dtp->dt_options[option] = val;
	return (0);
}