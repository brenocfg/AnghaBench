#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  dtrace_proginfo_t ;
typedef  int /*<<< orphan*/  dtrace_prog_t ;

/* Variables and functions */
 int /*<<< orphan*/  DTRACE_PROBESPEC_NAME ; 
 int /*<<< orphan*/  dfail (char*) ; 
 scalar_t__ dtrace_go (int /*<<< orphan*/ ) ; 
 int dtrace_program_exec (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dtrace_program_strcompile (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fputs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ g_Vflag ; 
 int /*<<< orphan*/  g_dtp ; 
 int /*<<< orphan*/  g_prog ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
dprog_compile()
{
	dtrace_prog_t *prog;
	dtrace_proginfo_t info;

	if (g_Vflag) {
		(void) fprintf(stderr, "lockstat: vvvv D program vvvv\n");
		(void) fputs(g_prog, stderr);
		(void) fprintf(stderr, "lockstat: ^^^^ D program ^^^^\n");
	}

	if ((prog = dtrace_program_strcompile(g_dtp, g_prog,
	    DTRACE_PROBESPEC_NAME, 0, 0, NULL)) == NULL)
		dfail("failed to compile program");

	if (dtrace_program_exec(g_dtp, prog, &info) == -1)
		dfail("failed to enable probes");

	if (dtrace_go(g_dtp) != 0)
		dfail("couldn't start tracing");
}