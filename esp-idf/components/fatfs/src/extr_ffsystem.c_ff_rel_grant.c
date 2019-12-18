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
typedef  int /*<<< orphan*/  FF_SYNC_t ;

/* Variables and functions */
 int /*<<< orphan*/  ReleaseMutex (int /*<<< orphan*/ ) ; 

void ff_rel_grant (
	FF_SYNC_t sobj	/* Sync object to be signaled */
)
{
	/* Win32 */
	ReleaseMutex(sobj);

	/* uITRON */
//	sig_sem(sobj);

	/* uC/OS-II */
//	OSMutexPost(sobj);

	/* FreeRTOS */
//	xSemaphoreGive(sobj);

	/* CMSIS-RTOS */
//	osMutexRelease(sobj);
}