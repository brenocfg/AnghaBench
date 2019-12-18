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
struct TYPE_3__ {int /*<<< orphan*/  dc_name; int /*<<< orphan*/  dc_desc; int /*<<< orphan*/  dc_ofile; int /*<<< orphan*/  dc_prog; int /*<<< orphan*/  dc_arg; } ;
typedef  TYPE_1__ dtrace_cmd_t ;

/* Variables and functions */
 int /*<<< orphan*/  DTRACE_D_PROBES ; 
 char* basename (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dfatal (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dtrace_program_link (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int g_cmdc ; 
 int g_cmdv ; 
 int /*<<< orphan*/  g_dtp ; 
 int /*<<< orphan*/  g_objc ; 
 int /*<<< orphan*/  g_objv ; 
 int /*<<< orphan*/ * g_ofile ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,...) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 char* strrchr (int /*<<< orphan*/ ,char) ; 

__attribute__((used)) static void
link_prog(dtrace_cmd_t *dcp)
{
	char *p;

	if (g_cmdc == 1 && g_ofile != NULL) {
		(void) strlcpy(dcp->dc_ofile, g_ofile, sizeof (dcp->dc_ofile));
	} else if ((p = strrchr(dcp->dc_arg, '.')) != NULL &&
	    strcmp(p, ".d") == 0) {
		p[0] = '\0'; /* strip .d suffix */
		(void) snprintf(dcp->dc_ofile, sizeof (dcp->dc_ofile),
		    "%s.o", basename(dcp->dc_arg));
	} else if (g_cmdc > 1) {
		(void) snprintf(dcp->dc_ofile, sizeof (dcp->dc_ofile),
		    "d.out.%td", dcp - g_cmdv);
	} else {
		(void) snprintf(dcp->dc_ofile, sizeof (dcp->dc_ofile),
		    "d.out");
	}

	if (dtrace_program_link(g_dtp, dcp->dc_prog, DTRACE_D_PROBES,
	    dcp->dc_ofile, g_objc, g_objv) != 0)
		dfatal("failed to link %s %s", dcp->dc_desc, dcp->dc_name);
}