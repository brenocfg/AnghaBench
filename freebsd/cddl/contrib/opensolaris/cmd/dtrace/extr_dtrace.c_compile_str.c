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
struct TYPE_3__ {char* dc_desc; int /*<<< orphan*/  dc_arg; int /*<<< orphan*/  dc_name; int /*<<< orphan*/  dc_spec; int /*<<< orphan*/ * dc_prog; } ;
typedef  TYPE_1__ dtrace_cmd_t ;

/* Variables and functions */
 int DTRACE_C_PSPEC ; 
 int /*<<< orphan*/  dfatal (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dtrace_program_strcompile (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_argc ; 
 int /*<<< orphan*/  g_argv ; 
 int g_cflags ; 
 int /*<<< orphan*/  g_dtp ; 
 char* strpbrk (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
compile_str(dtrace_cmd_t *dcp)
{
	char *p;

	if ((dcp->dc_prog = dtrace_program_strcompile(g_dtp, dcp->dc_arg,
	    dcp->dc_spec, g_cflags | DTRACE_C_PSPEC, g_argc, g_argv)) == NULL)
		dfatal("invalid probe specifier %s", dcp->dc_arg);

	if ((p = strpbrk(dcp->dc_arg, "{/;")) != NULL)
		*p = '\0'; /* crop name for reporting */

	dcp->dc_desc = "description";
	dcp->dc_name = dcp->dc_arg;
}