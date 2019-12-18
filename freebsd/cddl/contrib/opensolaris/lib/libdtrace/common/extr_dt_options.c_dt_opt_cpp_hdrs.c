#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * dt_pcb; } ;
typedef  TYPE_1__ dtrace_hdl_t ;

/* Variables and functions */
 int /*<<< orphan*/  EDT_BADOPTCTX ; 
 int /*<<< orphan*/  EDT_BADOPTVAL ; 
 int /*<<< orphan*/  EDT_NOMEM ; 
 int /*<<< orphan*/ * dt_cpp_add_arg (TYPE_1__*,char*) ; 
 int dt_set_errno (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dt_opt_cpp_hdrs(dtrace_hdl_t *dtp, const char *arg, uintptr_t option)
{
	if (arg != NULL)
		return (dt_set_errno(dtp, EDT_BADOPTVAL));

	if (dtp->dt_pcb != NULL)
		return (dt_set_errno(dtp, EDT_BADOPTCTX));

	if (dt_cpp_add_arg(dtp, "-H") == NULL)
		return (dt_set_errno(dtp, EDT_NOMEM));

	return (0);
}