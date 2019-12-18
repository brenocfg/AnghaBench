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
 int /*<<< orphan*/  FF_FS_TIMEOUT ; 
 scalar_t__ WAIT_OBJECT_0 ; 
 scalar_t__ WaitForSingleObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ff_req_grant (	/* 1:Got a grant to access the volume, 0:Could not get a grant */
	FF_SYNC_t sobj	/* Sync object to wait */
)
{
	/* Win32 */
	return (int)(WaitForSingleObject(sobj, FF_FS_TIMEOUT) == WAIT_OBJECT_0);

	/* uITRON */
//	return (int)(wai_sem(sobj) == E_OK);

	/* uC/OS-II */
//	OS_ERR err;
//	OSMutexPend(sobj, FF_FS_TIMEOUT, &err));
//	return (int)(err == OS_NO_ERR);

	/* FreeRTOS */
//	return (int)(xSemaphoreTake(sobj, FF_FS_TIMEOUT) == pdTRUE);

	/* CMSIS-RTOS */
//	return (int)(osMutexWait(sobj, FF_FS_TIMEOUT) == osOK);
}