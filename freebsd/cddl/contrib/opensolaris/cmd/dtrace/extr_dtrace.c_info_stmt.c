#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_3__* dtsd_ecbdesc; } ;
typedef  TYPE_1__ dtrace_stmtdesc_t ;
typedef  int /*<<< orphan*/  dtrace_prog_t ;
typedef  int /*<<< orphan*/  dtrace_probeinfo_t ;
struct TYPE_8__ {int /*<<< orphan*/  dtpd_name; int /*<<< orphan*/  dtpd_func; int /*<<< orphan*/  dtpd_mod; int /*<<< orphan*/  dtpd_provider; } ;
typedef  TYPE_2__ dtrace_probedesc_t ;
typedef  int /*<<< orphan*/  dtrace_hdl_t ;
struct TYPE_9__ {TYPE_2__ dted_probe; } ;
typedef  TYPE_3__ dtrace_ecbdesc_t ;

/* Variables and functions */
 scalar_t__ dtrace_probe_info (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oprintf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_probe_info (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
info_stmt(dtrace_hdl_t *dtp, dtrace_prog_t *pgp,
    dtrace_stmtdesc_t *stp, dtrace_ecbdesc_t **last)
{
	dtrace_ecbdesc_t *edp = stp->dtsd_ecbdesc;
	dtrace_probedesc_t *pdp = &edp->dted_probe;
	dtrace_probeinfo_t p;

	if (edp == *last)
		return (0);

	oprintf("\n%s:%s:%s:%s\n",
	    pdp->dtpd_provider, pdp->dtpd_mod, pdp->dtpd_func, pdp->dtpd_name);

	if (dtrace_probe_info(dtp, pdp, &p) == 0)
		print_probe_info(&p);

	*last = edp;
	return (0);
}