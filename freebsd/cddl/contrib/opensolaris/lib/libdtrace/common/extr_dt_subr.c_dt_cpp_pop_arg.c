#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int dt_cpp_argc; char** dt_cpp_argv; } ;
typedef  TYPE_1__ dtrace_hdl_t ;

/* Variables and functions */

char *
dt_cpp_pop_arg(dtrace_hdl_t *dtp)
{
	char *arg;

	if (dtp->dt_cpp_argc <= 1)
		return (NULL); /* dt_cpp_argv[0] cannot be popped */

	arg = dtp->dt_cpp_argv[--dtp->dt_cpp_argc];
	dtp->dt_cpp_argv[dtp->dt_cpp_argc] = NULL;

	return (arg);
}