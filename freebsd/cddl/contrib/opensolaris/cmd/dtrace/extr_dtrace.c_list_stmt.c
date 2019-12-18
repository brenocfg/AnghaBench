#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* dtsd_ecbdesc; } ;
typedef  TYPE_1__ dtrace_stmtdesc_t ;
typedef  int /*<<< orphan*/  dtrace_prog_t ;
typedef  int /*<<< orphan*/  dtrace_hdl_t ;
struct TYPE_8__ {char* dtpd_mod; int /*<<< orphan*/  dtpd_provider; int /*<<< orphan*/  dtpd_name; int /*<<< orphan*/  dtpd_func; } ;
struct TYPE_7__ {TYPE_5__ dted_probe; } ;
typedef  TYPE_2__ dtrace_ecbdesc_t ;

/* Variables and functions */
 int /*<<< orphan*/  dtrace_errmsg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dtrace_errno (int /*<<< orphan*/ *) ; 
 scalar_t__ dtrace_probe_iter (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_dtp ; 
 int /*<<< orphan*/  list_probe ; 

__attribute__((used)) static int
list_stmt(dtrace_hdl_t *dtp, dtrace_prog_t *pgp,
    dtrace_stmtdesc_t *stp, dtrace_ecbdesc_t **last)
{
	dtrace_ecbdesc_t *edp = stp->dtsd_ecbdesc;

	if (edp == *last)
		return (0);

	if (dtrace_probe_iter(g_dtp, &edp->dted_probe, list_probe, NULL) != 0) {
		error("failed to match %s:%s:%s:%s: %s\n",
		    edp->dted_probe.dtpd_provider, edp->dted_probe.dtpd_mod,
		    edp->dted_probe.dtpd_func, edp->dted_probe.dtpd_name,
		    dtrace_errmsg(dtp, dtrace_errno(dtp)));
	}

	*last = edp;
	return (0);
}