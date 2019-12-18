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

/* Variables and functions */
 int /*<<< orphan*/  DSM_HANDLE_INVALID ; 
 int /*<<< orphan*/  currentProgressDSMHandle ; 
 int /*<<< orphan*/  dsm_detach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dsm_find_mapping (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgstat_progress_end_command () ; 

void
FinalizeCurrentProgressMonitor(void)
{
	dsm_segment *dsmSegment = dsm_find_mapping(currentProgressDSMHandle);

	if (dsmSegment != NULL)
	{
		dsm_detach(dsmSegment);
	}

	pgstat_progress_end_command();

	currentProgressDSMHandle = DSM_HANDLE_INVALID;
}