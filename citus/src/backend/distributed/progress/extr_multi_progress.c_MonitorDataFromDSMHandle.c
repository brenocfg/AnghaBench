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
typedef  int /*<<< orphan*/  dsm_segment ;
typedef  int /*<<< orphan*/  dsm_handle ;
struct TYPE_3__ {void* steps; } ;
typedef  TYPE_1__ ProgressMonitorData ;

/* Variables and functions */
 int /*<<< orphan*/ * dsm_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dsm_find_mapping (int /*<<< orphan*/ ) ; 
 scalar_t__ dsm_segment_address (int /*<<< orphan*/ *) ; 

ProgressMonitorData *
MonitorDataFromDSMHandle(dsm_handle dsmHandle, dsm_segment **attachedSegment)
{
	dsm_segment *dsmSegment = dsm_find_mapping(dsmHandle);
	ProgressMonitorData *monitor = NULL;

	if (dsmSegment == NULL)
	{
		dsmSegment = dsm_attach(dsmHandle);
	}

	if (dsmSegment != NULL)
	{
		monitor = (ProgressMonitorData *) dsm_segment_address(dsmSegment);
		monitor->steps = (void *) (monitor + 1);
		*attachedSegment = dsmSegment;
	}

	return monitor;
}