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
 int CHASSIS_RESOLUTION_MS ; 
 int CHASSIS_RESOLUTION_SEC ; 

void chassis_set_logtimestamp_resolution(chassis_log *log, int res) {
	if (log == NULL)
		return;
	/* only set resolution to valid values, ignore otherwise */
	if (res == CHASSIS_RESOLUTION_SEC || res == CHASSIS_RESOLUTION_MS)
		log->log_ts_resolution = res;
}