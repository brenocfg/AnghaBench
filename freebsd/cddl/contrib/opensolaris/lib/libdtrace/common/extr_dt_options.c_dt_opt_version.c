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
typedef  int /*<<< orphan*/  dtrace_hdl_t ;
typedef  int /*<<< orphan*/  dt_version_t ;

/* Variables and functions */
 int /*<<< orphan*/  EDT_BADOPTVAL ; 
 int /*<<< orphan*/  EDT_VERSINVAL ; 
 int /*<<< orphan*/  EDT_VERSUNDEF ; 
 int dt_reduce (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int dt_set_errno (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_version_defined (int /*<<< orphan*/ ) ; 
 int dt_version_str2num (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
dt_opt_version(dtrace_hdl_t *dtp, const char *arg, uintptr_t option)
{
	dt_version_t v;

	if (arg == NULL)
		return (dt_set_errno(dtp, EDT_BADOPTVAL));

	if (dt_version_str2num(arg, &v) == -1)
		return (dt_set_errno(dtp, EDT_VERSINVAL));

	if (!dt_version_defined(v))
		return (dt_set_errno(dtp, EDT_VERSUNDEF));

	return (dt_reduce(dtp, v));
}