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
typedef  scalar_t__ FF_SYNC_t ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 scalar_t__ CreateMutex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 

int ff_cre_syncobj (	/* 1:Function succeeded, 0:Could not create the sync object */
	BYTE vol,			/* Corresponding volume (logical drive number) */
	FF_SYNC_t* sobj		/* Pointer to return the created sync object */
)
{
	/* Win32 */
	*sobj = CreateMutex(NULL, FALSE, NULL);
	return (int)(*sobj != INVALID_HANDLE_VALUE);

	/* uITRON */
//	T_CSEM csem = {TA_TPRI,1,1};
//	*sobj = acre_sem(&csem);
//	return (int)(*sobj > 0);

	/* uC/OS-II */
//	OS_ERR err;
//	*sobj = OSMutexCreate(0, &err);
//	return (int)(err == OS_NO_ERR);

	/* FreeRTOS */
//	*sobj = xSemaphoreCreateMutex();
//	return (int)(*sobj != NULL);

	/* CMSIS-RTOS */
//	*sobj = osMutexCreate(&Mutex[vol]);
//	return (int)(*sobj != NULL);
}