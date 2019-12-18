#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* dt_procs; } ;
typedef  TYPE_2__ dtrace_hdl_t ;
struct TYPE_5__ {int dph_lrulim; } ;

/* Variables and functions */
 int /*<<< orphan*/  EDT_BADOPTVAL ; 
 int atoi (char const*) ; 
 int dt_set_errno (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dt_opt_pgmax(dtrace_hdl_t *dtp, const char *arg, uintptr_t option)
{
	int n;

	if (arg == NULL || (n = atoi(arg)) < 0)
		return (dt_set_errno(dtp, EDT_BADOPTVAL));

	dtp->dt_procs->dph_lrulim = n;
	return (0);
}