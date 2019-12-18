#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pd ;
struct TYPE_14__ {int /*<<< orphan*/  dt_errno; } ;
typedef  TYPE_1__ dtrace_hdl_t ;
typedef  int (* dtrace_aggregate_walk_f ) (TYPE_1__*,int /*<<< orphan*/ ,TYPE_3__*) ;
struct TYPE_15__ {int dtpa_allunprint; int /*<<< orphan*/ * dtpa_fp; TYPE_1__* dtpa_dtp; } ;
typedef  TYPE_3__ dt_print_aggdata_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  bzero (TYPE_3__*,int) ; 
 int /*<<< orphan*/  dt_print_agg ; 
 int dt_set_errno (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int dtrace_aggregate_walk_sorted (TYPE_1__*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int stub1 (TYPE_1__*,int /*<<< orphan*/ ,TYPE_3__*) ; 

int
dtrace_aggregate_print(dtrace_hdl_t *dtp, FILE *fp,
    dtrace_aggregate_walk_f *func)
{
	dt_print_aggdata_t pd;

	bzero(&pd, sizeof (pd));

	pd.dtpa_dtp = dtp;
	pd.dtpa_fp = fp;
	pd.dtpa_allunprint = 1;

	if (func == NULL)
		func = dtrace_aggregate_walk_sorted;

	if ((*func)(dtp, dt_print_agg, &pd) == -1)
		return (dt_set_errno(dtp, dtp->dt_errno));

	return (0);
}