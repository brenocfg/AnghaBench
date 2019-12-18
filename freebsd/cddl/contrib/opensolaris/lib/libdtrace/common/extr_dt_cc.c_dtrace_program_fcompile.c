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
typedef  int /*<<< orphan*/  uint_t ;
typedef  int /*<<< orphan*/  dtrace_prog_t ;
typedef  int /*<<< orphan*/  dtrace_hdl_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  DTRACE_PROBESPEC_NAME ; 
 int /*<<< orphan*/  DT_CTX_DPROG ; 
 int /*<<< orphan*/ * dt_compile (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char* const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

dtrace_prog_t *
dtrace_program_fcompile(dtrace_hdl_t *dtp, FILE *fp,
    uint_t cflags, int argc, char *const argv[])
{
	return (dt_compile(dtp, DT_CTX_DPROG,
	    DTRACE_PROBESPEC_NAME, NULL, cflags, argc, argv, fp, NULL));
}