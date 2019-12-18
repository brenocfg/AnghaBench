#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dtrace_hdl_t ;
struct TYPE_4__ {scalar_t__ dpr_pid; } ;
typedef  TYPE_1__ dt_proc_t ;

/* Variables and functions */
 int /*<<< orphan*/  DT_PROC_STOP_MAIN ; 
 int /*<<< orphan*/  dt_dprintf (char*,int,char const*) ; 
 int /*<<< orphan*/  dt_proc_stop (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dt_proc_bpmain(dtrace_hdl_t *dtp, dt_proc_t *dpr, const char *fname)
{
	dt_dprintf("pid %d: breakpoint at %s()\n", (int)dpr->dpr_pid, fname);
	dt_proc_stop(dpr, DT_PROC_STOP_MAIN);
}