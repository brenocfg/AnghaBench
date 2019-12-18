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
struct TYPE_3__ {int log_file_fd; int /*<<< orphan*/  log_filename; } ;
typedef  TYPE_1__ chassis_log ;

/* Variables and functions */
 int O_APPEND ; 
 int O_CREAT ; 
 int O_RDWR ; 
 int TRUE ; 
 int open (int /*<<< orphan*/ ,int,int) ; 

int chassis_log_open(chassis_log *log) {
	if (!log->log_filename) return TRUE;

	log->log_file_fd = open(log->log_filename, O_RDWR | O_CREAT | O_APPEND, 0660);

	return (log->log_file_fd != -1);
}