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
 scalar_t__ CloseHandle (int /*<<< orphan*/ ) ; 

int ff_del_syncobj (	/* 1:Function succeeded, 0:Could not delete due to an error */
	FF_SYNC_t sobj		/* Sync object tied to the logical drive to be deleted */
)
{
	/* Win32 */
	return (int)CloseHandle(sobj);

	/* uITRON */
//	return (int)(del_sem(sobj) == E_OK);

	/* uC/OS-II */
//	OS_ERR err;
//	OSMutexDel(sobj, OS_DEL_ALWAYS, &err);
//	return (int)(err == OS_NO_ERR);

	/* FreeRTOS */
//  vSemaphoreDelete(sobj);
//	return 1;

	/* CMSIS-RTOS */
//	return (int)(osMutexDelete(sobj) == osOK);
}