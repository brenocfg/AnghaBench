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
struct TYPE_3__ {int log_file_fd; } ;
typedef  TYPE_1__ chassis_log ;

/* Variables and functions */
 int /*<<< orphan*/  close (int) ; 

int chassis_log_close(chassis_log *log) {
	if (log->log_file_fd == -1) return 0;

	close(log->log_file_fd);

	log->log_file_fd = -1;

	return 0;
}