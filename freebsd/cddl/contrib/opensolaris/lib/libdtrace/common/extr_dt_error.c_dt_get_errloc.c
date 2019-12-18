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
struct TYPE_3__ {char* dt_errfile; int dt_errline; } ;
typedef  TYPE_1__ dtrace_hdl_t ;

/* Variables and functions */

void dt_get_errloc(dtrace_hdl_t *dtp, const char **p_errfile, int *p_errline)
{
	*p_errfile = dtp->dt_errfile;
	*p_errline = dtp->dt_errline;
}