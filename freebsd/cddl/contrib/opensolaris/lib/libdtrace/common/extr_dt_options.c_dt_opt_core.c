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

/* Variables and functions */
 int /*<<< orphan*/  EDT_BADOPTVAL ; 
 scalar_t__ atexit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_coredump ; 
 int dt_set_errno (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 

__attribute__((used)) static int
dt_opt_core(dtrace_hdl_t *dtp, const char *arg, uintptr_t option)
{
	static int enabled = 0;

	if (arg != NULL)
		return (dt_set_errno(dtp, EDT_BADOPTVAL));

	if (enabled++ || atexit(dt_coredump) == 0)
		return (0);

	return (dt_set_errno(dtp, errno));
}