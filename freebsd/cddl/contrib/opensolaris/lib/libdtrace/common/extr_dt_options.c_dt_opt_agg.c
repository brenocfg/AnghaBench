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
struct TYPE_6__ {uintptr_t dtat_flags; } ;
struct TYPE_5__ {TYPE_2__ dt_aggregate; } ;
typedef  TYPE_1__ dtrace_hdl_t ;
typedef  TYPE_2__ dt_aggregate_t ;

/* Variables and functions */
 int /*<<< orphan*/  EDT_BADOPTVAL ; 
 int dt_set_errno (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dt_opt_agg(dtrace_hdl_t *dtp, const char *arg, uintptr_t option)
{
	dt_aggregate_t *agp = &dtp->dt_aggregate;

	if (arg != NULL)
		return (dt_set_errno(dtp, EDT_BADOPTVAL));

	agp->dtat_flags |= option;
	return (0);
}