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
typedef  int /*<<< orphan*/  proc_t ;

/* Variables and functions */
 int PROC_RETURNED ; 
 int /*<<< orphan*/  dtrace_lazy_dofs_process (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
dtrace_lazy_dofs_proc_iterate_doit(proc_t *p, void* ignored)
{
#pragma unused(ignored)

	dtrace_lazy_dofs_process(p);

	return PROC_RETURNED;
}