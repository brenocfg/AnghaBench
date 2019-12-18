#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int log_file_fd; scalar_t__ event_source_handle; scalar_t__ use_windows_applog; scalar_t__ use_syslog; } ;
typedef  TYPE_1__ chassis_log ;
struct TYPE_9__ {int /*<<< orphan*/  win_evtype; int /*<<< orphan*/  syslog_lvl; } ;
struct TYPE_8__ {char* str; } ;
typedef  TYPE_2__ GString ;

/* Variables and functions */
 int G_LOG_ERROR_POSITION ; 
 int G_LOG_LEVEL_MASK ; 
 int /*<<< orphan*/  ReportEvent (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S (TYPE_2__*) ; 
 int STDERR_FILENO ; 
 int g_bit_nth_lsf (int,int) ; 
 TYPE_3__* log_lvl_map ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,char*) ; 
 int write (int,char*,...) ; 

__attribute__((used)) static int chassis_log_write(chassis_log *log, int log_level, GString *str) {
	if (-1 != log->log_file_fd) {
		/* prepend a timestamp */
		if (-1 == write(log->log_file_fd, S(str))) {
			/* writing to the file failed (Disk Full, what ever ... */
			
			write(STDERR_FILENO, S(str));
			write(STDERR_FILENO, "\n", 1);
		} else {
			write(log->log_file_fd, "\n", 1);
		}
#ifdef HAVE_SYSLOG_H
	} else if (log->use_syslog) {
		int log_index = g_bit_nth_lsf(log_level & G_LOG_LEVEL_MASK, -1) - G_LOG_ERROR_POSITION;
		syslog(log_lvl_map[log_index].syslog_lvl, "%s", str->str);
#endif
#ifdef _WIN32
	} else if (log->use_windows_applog && log->event_source_handle) {
		char *log_messages[1];
		int log_index = g_bit_nth_lsf(log_level & G_LOG_LEVEL_MASK, -1) - G_LOG_ERROR_POSITION;

		log_messages[0] = str->str;
		ReportEvent(log->event_source_handle,
					log_lvl_map[log_index].win_evtype,
					0, /* category, we don't have that yet */
					log_lvl_map[log_index].win_evtype, /* event indentifier, one of MSG_ERROR (0x01), MSG_WARNING(0x02), MSG_INFO(0x04) */
					NULL,
					1, /* number of strings to be substituted */
					0, /* no event specific data */
					log_messages,	/* the actual log message, always the message we came up with, we don't localize using Windows message files*/
					NULL);
#endif
	} else {
		write(STDERR_FILENO, S(str));
		write(STDERR_FILENO, "\n", 1);
	}

	return 0;
}