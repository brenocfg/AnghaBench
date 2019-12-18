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
typedef  int /*<<< orphan*/  dsm_segment ;
typedef  int /*<<< orphan*/  ProgressMonitorData ;

/* Variables and functions */
 int /*<<< orphan*/ * MonitorDataFromDSMHandle (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  currentProgressDSMHandle ; 

ProgressMonitorData *
GetCurrentProgressMonitor(void)
{
	dsm_segment *dsmSegment = NULL;
	ProgressMonitorData *monitor = MonitorDataFromDSMHandle(currentProgressDSMHandle,
															&dsmSegment);

	return monitor;
}