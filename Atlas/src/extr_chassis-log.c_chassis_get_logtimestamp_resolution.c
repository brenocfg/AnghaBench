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
struct TYPE_3__ {int log_ts_resolution; } ;
typedef  TYPE_1__ chassis_log ;

/* Variables and functions */

int chassis_get_logtimestamp_resolution(chassis_log *log) {
	if (log == NULL)
		return -1;
	return log->log_ts_resolution;
}