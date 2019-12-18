#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dtrace_stmt_f ;
struct TYPE_9__ {int /*<<< orphan*/  dtat_class; int /*<<< orphan*/  dtat_data; int /*<<< orphan*/  dtat_name; } ;
struct TYPE_8__ {int /*<<< orphan*/  dtat_class; int /*<<< orphan*/  dtat_data; int /*<<< orphan*/  dtat_name; } ;
struct TYPE_10__ {int dpi_matches; TYPE_2__ dpi_stmtattr; TYPE_1__ dpi_descattr; } ;
typedef  TYPE_3__ dtrace_proginfo_t ;
typedef  int /*<<< orphan*/  dtrace_ecbdesc_t ;
struct TYPE_11__ {int /*<<< orphan*/  dc_prog; int /*<<< orphan*/  dc_name; int /*<<< orphan*/  dc_desc; } ;
typedef  TYPE_4__ dtrace_cmd_t ;

/* Variables and functions */
 int /*<<< orphan*/  dfatal (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dtrace_class_name (int /*<<< orphan*/ ) ; 
 int dtrace_program_exec (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  dtrace_program_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  dtrace_stability_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dtrace_stmt_iter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  g_dtp ; 
 int /*<<< orphan*/  g_exec ; 
 int g_total ; 
 scalar_t__ g_verbose ; 
 scalar_t__ info_stmt ; 
 int /*<<< orphan*/  notice (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  oprintf (char*,...) ; 

__attribute__((used)) static void
exec_prog(const dtrace_cmd_t *dcp)
{
	dtrace_ecbdesc_t *last = NULL;
	dtrace_proginfo_t dpi;

	if (!g_exec) {
		dtrace_program_info(g_dtp, dcp->dc_prog, &dpi);
	} else if (dtrace_program_exec(g_dtp, dcp->dc_prog, &dpi) == -1) {
		dfatal("failed to enable '%s'", dcp->dc_name);
	} else {
		notice("%s '%s' matched %u probe%s\n",
		    dcp->dc_desc, dcp->dc_name,
		    dpi.dpi_matches, dpi.dpi_matches == 1 ? "" : "s");
	}

	if (g_verbose) {
		oprintf("\nStability attributes for %s %s:\n",
		    dcp->dc_desc, dcp->dc_name);

		oprintf("\n\tMinimum Probe Description Attributes\n");
		oprintf("\t\tIdentifier Names: %s\n",
		    dtrace_stability_name(dpi.dpi_descattr.dtat_name));
		oprintf("\t\tData Semantics:   %s\n",
		    dtrace_stability_name(dpi.dpi_descattr.dtat_data));
		oprintf("\t\tDependency Class: %s\n",
		    dtrace_class_name(dpi.dpi_descattr.dtat_class));

		oprintf("\n\tMinimum Statement Attributes\n");

		oprintf("\t\tIdentifier Names: %s\n",
		    dtrace_stability_name(dpi.dpi_stmtattr.dtat_name));
		oprintf("\t\tData Semantics:   %s\n",
		    dtrace_stability_name(dpi.dpi_stmtattr.dtat_data));
		oprintf("\t\tDependency Class: %s\n",
		    dtrace_class_name(dpi.dpi_stmtattr.dtat_class));

		if (!g_exec) {
			(void) dtrace_stmt_iter(g_dtp, dcp->dc_prog,
			    (dtrace_stmt_f *)info_stmt, &last);
		} else
			oprintf("\n");
	}

	g_total += dpi.dpi_matches;
}