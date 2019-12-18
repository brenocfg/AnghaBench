#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UBaseType_t ;
struct TYPE_6__ {scalar_t__ uxPriority; } ;
struct TYPE_5__ {size_t xCoreID; scalar_t__ uxPriority; int /*<<< orphan*/  xEventListItem; int /*<<< orphan*/  xGenericListItem; } ;
typedef  TYPE_1__ TCB_t ;
typedef  int /*<<< orphan*/  List_t ;
typedef  scalar_t__ BaseType_t ;

/* Variables and functions */
 int /*<<< orphan*/  configASSERT (TYPE_1__*) ; 
 scalar_t__ listGET_OWNER_OF_HEAD_ENTRY (int /*<<< orphan*/  const* const) ; 
 scalar_t__ listLIST_IS_EMPTY (int /*<<< orphan*/  const* const) ; 
 scalar_t__ pdFALSE ; 
 scalar_t__ pdTRUE ; 
 size_t portNUM_PROCESSORS ; 
 int /*<<< orphan*/  prvAddTaskToReadyList (TYPE_1__*) ; 
 int /*<<< orphan*/  prvResetNextTaskUnblockTime () ; 
 TYPE_2__** pxCurrentTCB ; 
 int /*<<< orphan*/  taskENTER_CRITICAL_ISR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskEXIT_CRITICAL_ISR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskYIELD_OTHER_CORE (size_t,scalar_t__) ; 
 scalar_t__ tskCAN_RUN_HERE (size_t) ; 
 size_t tskNO_AFFINITY ; 
 int /*<<< orphan*/  uxListRemove (int /*<<< orphan*/ *) ; 
 size_t* uxSchedulerSuspended ; 
 int /*<<< orphan*/  vListInsertEnd (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xPendingReadyList ; 
 size_t xPortGetCoreID () ; 
 int /*<<< orphan*/  xTaskQueueMutex ; 
 scalar_t__* xYieldPending ; 

BaseType_t xTaskRemoveFromEventList( const List_t * const pxEventList )
{
TCB_t *pxUnblockedTCB;
BaseType_t xReturn;
BaseType_t xTaskCanBeReady;
UBaseType_t i, uxTargetCPU;

	/* THIS FUNCTION MUST BE CALLED FROM A CRITICAL SECTION.  It can also be
	called from a critical section within an ISR. */
	taskENTER_CRITICAL_ISR(&xTaskQueueMutex);
	/* The event list is sorted in priority order, so the first in the list can
	be removed as it is known to be the highest priority.  Remove the TCB from
	the delayed list, and add it to the ready list.

	If an event is for a queue that is locked then this function will never
	get called - the lock count on the queue will get modified instead.  This
	means exclusive access to the event list is guaranteed here.

	This function assumes that a check has already been made to ensure that
	pxEventList is not empty. */
	if ( ( listLIST_IS_EMPTY( pxEventList ) ) == pdFALSE ) {
		pxUnblockedTCB = ( TCB_t * ) listGET_OWNER_OF_HEAD_ENTRY( pxEventList );
		configASSERT( pxUnblockedTCB );
		( void ) uxListRemove( &( pxUnblockedTCB->xEventListItem ) );
	} else {
		taskEXIT_CRITICAL_ISR(&xTaskQueueMutex);
		return pdFALSE;
	}

	/* Determine if the task can possibly be run on either CPU now, either because the scheduler
	   the task is pinned to is running or because a scheduler is running on any CPU. */
	xTaskCanBeReady = pdFALSE;
	if ( pxUnblockedTCB->xCoreID == tskNO_AFFINITY ) {
		uxTargetCPU = xPortGetCoreID();
		for (i = 0; i < portNUM_PROCESSORS; i++) {
			if ( uxSchedulerSuspended[ i ] == ( UBaseType_t ) pdFALSE ) {
				xTaskCanBeReady = pdTRUE;
				break;
			}
		}
	} else {
		uxTargetCPU = pxUnblockedTCB->xCoreID;
		xTaskCanBeReady = uxSchedulerSuspended[ uxTargetCPU ] == ( UBaseType_t ) pdFALSE;

	}

	if( xTaskCanBeReady )
	{
		( void ) uxListRemove( &( pxUnblockedTCB->xGenericListItem ) );
		prvAddTaskToReadyList( pxUnblockedTCB );
	}
	else
	{
		/* The delayed and ready lists cannot be accessed, so hold this task
		pending until the scheduler is resumed on this CPU. */
		vListInsertEnd( &( xPendingReadyList[ uxTargetCPU ] ), &( pxUnblockedTCB->xEventListItem ) );
	}

	if ( tskCAN_RUN_HERE(pxUnblockedTCB->xCoreID) && pxUnblockedTCB->uxPriority >= pxCurrentTCB[ xPortGetCoreID() ]->uxPriority )
	{
		/* Return true if the task removed from the event list has a higher
		priority than the calling task.  This allows the calling task to know if
		it should force a context switch now. */
		xReturn = pdTRUE;

		/* Mark that a yield is pending in case the user is not using the
		"xHigherPriorityTaskWoken" parameter to an ISR safe FreeRTOS function. */
		xYieldPending[ xPortGetCoreID() ] = pdTRUE;
	}
	else if ( pxUnblockedTCB->xCoreID != xPortGetCoreID() )
	{
		taskYIELD_OTHER_CORE( pxUnblockedTCB->xCoreID, pxUnblockedTCB->uxPriority );
		xReturn = pdFALSE;
	}
	else
	{
		xReturn = pdFALSE;
	}

	#if( configUSE_TICKLESS_IDLE == 1 )
	{
		/* If a task is blocked on a kernel object then xNextTaskUnblockTime
		might be set to the blocked task's time out time.  If the task is
		unblocked for a reason other than a timeout xNextTaskUnblockTime is
		normally left unchanged, because it is automatically get reset to a new
		value when the tick count equals xNextTaskUnblockTime.  However if
		tickless idling is used it might be more important to enter sleep mode
		at the earliest possible time - so reset xNextTaskUnblockTime here to
		ensure it is updated at the earliest possible time. */
		prvResetNextTaskUnblockTime();
	}
	#endif
	taskEXIT_CRITICAL_ISR(&xTaskQueueMutex);

	return xReturn;
}