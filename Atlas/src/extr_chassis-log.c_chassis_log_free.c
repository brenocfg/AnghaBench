#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* log_filename; int /*<<< orphan*/  last_msg; int /*<<< orphan*/  log_ts_str; scalar_t__ event_source_handle; } ;
typedef  TYPE_1__ chassis_log ;

/* Variables and functions */
 int /*<<< orphan*/  DeregisterEventSource (scalar_t__) ; 
 int GetLastError () ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  chassis_log_close (TYPE_1__*) ; 
 int /*<<< orphan*/  g_critical (char*,int) ; 
 int /*<<< orphan*/  g_free (TYPE_1__*) ; 
 int /*<<< orphan*/  g_string_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void chassis_log_free(chassis_log *log) {
	if (!log) return;

	chassis_log_close(log);
#ifdef _WIN32
	if (log->event_source_handle) {
		if (!DeregisterEventSource(log->event_source_handle)) {
			int err = GetLastError();
			g_critical("unhandled error-code (%d) for DeregisterEventSource()", err);
		}
	}
#endif
	g_string_free(log->log_ts_str, TRUE);
	g_string_free(log->last_msg, TRUE);

	if (log->log_filename) g_free(log->log_filename);

	g_free(log);
}