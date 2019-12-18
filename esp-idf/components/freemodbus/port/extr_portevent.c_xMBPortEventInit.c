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
typedef  int /*<<< orphan*/  eMBEventType ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MB_EVENT_QUEUE_SIZE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  vQueueAddToRegistry (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * xQueueCreate (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * xQueueHdl ; 

BOOL
xMBPortEventInit( void )
{
    BOOL bStatus = FALSE;
    if((xQueueHdl = xQueueCreate(MB_EVENT_QUEUE_SIZE, sizeof(eMBEventType))) != NULL)
    {
        vQueueAddToRegistry(xQueueHdl, "MbPortEventQueue");
        bStatus = TRUE;
    }
    return bStatus;
}