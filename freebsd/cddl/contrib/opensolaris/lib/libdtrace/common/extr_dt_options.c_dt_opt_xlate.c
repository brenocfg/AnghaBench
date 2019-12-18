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
struct TYPE_4__ {int /*<<< orphan*/  dt_xlatemode; } ;
typedef  TYPE_1__ dtrace_hdl_t ;

/* Variables and functions */
 int /*<<< orphan*/  DT_XL_DYNAMIC ; 
 int /*<<< orphan*/  DT_XL_STATIC ; 
 int /*<<< orphan*/  EDT_BADOPTVAL ; 
 int dt_set_errno (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int
dt_opt_xlate(dtrace_hdl_t *dtp, const char *arg, uintptr_t option)
{
	if (arg == NULL)
		return (dt_set_errno(dtp, EDT_BADOPTVAL));

	if (strcmp(arg, "dynamic") == 0)
		dtp->dt_xlatemode = DT_XL_DYNAMIC;
	else if (strcmp(arg, "static") == 0)
		dtp->dt_xlatemode = DT_XL_STATIC;
	else
		return (dt_set_errno(dtp, EDT_BADOPTVAL));

	return (0);
}