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
typedef  TYPE_1__* proc_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_3__ {char* p_name; int /*<<< orphan*/  p_pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  OS_LOG_DEFAULT ; 
 TYPE_1__* current_proc () ; 
 int /*<<< orphan*/  os_log_with_startup_serial (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,char*,char*,int const,char*) ; 

void
memorystatus_log_exception(const int max_footprint_mb, boolean_t memlimit_is_active, boolean_t memlimit_is_fatal)
{
	proc_t p = current_proc();

	/*
	 * The limit violation is logged here, but only once per process per limit.
	 * Soft memory limit is a non-fatal high-water-mark
	 * Hard memory limit is a fatal custom-task-limit or system-wide per-task memory limit.
	 */

	os_log_with_startup_serial(OS_LOG_DEFAULT, "EXC_RESOURCE -> %s[%d] exceeded mem limit: %s%s %d MB (%s)\n",
	       (*p->p_name ? p->p_name : "unknown"), p->p_pid, (memlimit_is_active ? "Active" : "Inactive"),
	       (memlimit_is_fatal  ? "Hard" : "Soft"), max_footprint_mb,
	       (memlimit_is_fatal  ? "fatal" : "non-fatal"));

	return;
}