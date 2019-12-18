#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UBaseType_t ;
struct TYPE_5__ {scalar_t__ uxPriority; } ;
struct TYPE_4__ {scalar_t__ uxPriority; int /*<<< orphan*/  xCoreID; int /*<<< orphan*/  xGenericListItem; int /*<<< orphan*/  xEventListItem; } ;
typedef  TYPE_1__ TCB_t ;
typedef  scalar_t__ BaseType_t ;

/* Variables and functions */
 int /*<<< orphan*/  configASSERT (int) ; 
 scalar_t__ listGET_OWNER_OF_HEAD_ENTRY (int /*<<< orphan*/ *) ; 
 scalar_t__ listLIST_IS_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtCOVERAGE_TEST_MARKER () ; 
 scalar_t__ pdFALSE ; 
 scalar_t__ pdTRUE ; 
 int /*<<< orphan*/  prvAddTaskToReadyList (TYPE_1__*) ; 
 TYPE_2__** pxCurrentTCB ; 
 int /*<<< orphan*/  taskENTER_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskEXIT_CRITICAL (int /*<<< orphan*/ *) ; 
 scalar_t__ taskSCHEDULER_RUNNING ; 
 int /*<<< orphan*/  taskYIELD_IF_USING_PREEMPTION () ; 
 scalar_t__ tskCAN_RUN_HERE (int /*<<< orphan*/ ) ; 
 scalar_t__ uxCurrentNumberOfTasks ; 
 int /*<<< orphan*/  uxListRemove (int /*<<< orphan*/ *) ; 
 scalar_t__ uxPendedTicks ; 
 scalar_t__* uxSchedulerSuspended ; 
 int /*<<< orphan*/ * xPendingReadyList ; 
 size_t xPortGetCoreID () ; 
 scalar_t__ xTaskGetSchedulerState () ; 
 scalar_t__ xTaskIncrementTick () ; 
 int /*<<< orphan*/  xTaskQueueMutex ; 
 scalar_t__* xYieldPending ; 

BaseType_t xTaskResumeAll( void )
{
TCB_t *pxTCB;
BaseType_t xAlreadyYielded = pdFALSE;

	/* If scheduler state is `taskSCHEDULER_RUNNING` then this function does not match a
	previous call to vTaskSuspendAll(). */
	configASSERT( xTaskGetSchedulerState() != taskSCHEDULER_RUNNING );
	/* It is possible that an ISR caused a task to be removed from an event
	list while the scheduler was suspended.  If this was the case then the
	removed task will have been added to the xPendingReadyList.  Once the
	scheduler has been resumed it is safe to move all the pending ready
	tasks from this list into their appropriate ready list. */

	taskENTER_CRITICAL(&xTaskQueueMutex);
	{
		--uxSchedulerSuspended[ xPortGetCoreID() ];

		if( uxSchedulerSuspended[ xPortGetCoreID() ] == ( UBaseType_t ) pdFALSE )
		{
			if( uxCurrentNumberOfTasks > ( UBaseType_t ) 0U )
			{
				/* Move any readied tasks from the pending list into the
				appropriate ready list. */
				while( listLIST_IS_EMPTY( &xPendingReadyList[ xPortGetCoreID() ] ) == pdFALSE )
				{
					pxTCB = ( TCB_t * ) listGET_OWNER_OF_HEAD_ENTRY( ( &xPendingReadyList[ xPortGetCoreID() ] ) );
					( void ) uxListRemove( &( pxTCB->xEventListItem ) );
					( void ) uxListRemove( &( pxTCB->xGenericListItem ) );
					prvAddTaskToReadyList( pxTCB );

					/* If the moved task has a priority higher than the current
					task then a yield must be performed. */
					if ( tskCAN_RUN_HERE(pxTCB->xCoreID) && pxTCB->uxPriority >= pxCurrentTCB[ xPortGetCoreID() ]->uxPriority )
					{
						/* We can schedule the awoken task on this CPU. */
						xYieldPending[xPortGetCoreID()] = pdTRUE;
					}
					else
					{
						mtCOVERAGE_TEST_MARKER();
					}
				}

				/* If any ticks occurred while the scheduler was suspended then
				they should be processed now.  This ensures the tick count does
				not	slip, and that any delayed tasks are resumed at the correct
				time. */
				if( uxPendedTicks > ( UBaseType_t ) 0U )
				{
					while( uxPendedTicks > ( UBaseType_t ) 0U )
					{
						if( xTaskIncrementTick() != pdFALSE )
						{
							xYieldPending[ xPortGetCoreID() ] = pdTRUE;
						}
						else
						{
							mtCOVERAGE_TEST_MARKER();
						}
						--uxPendedTicks;
					}
				}
				else
				{
					mtCOVERAGE_TEST_MARKER();
				}

				if( xYieldPending[ xPortGetCoreID() ] == pdTRUE )
				{
					#if( configUSE_PREEMPTION != 0 )
					{
						xAlreadyYielded = pdTRUE;
					}
					#endif
					taskYIELD_IF_USING_PREEMPTION();
				}
				else
				{
					mtCOVERAGE_TEST_MARKER();
				}
			}
		}
		else
		{
			mtCOVERAGE_TEST_MARKER();
		}
	}
	taskEXIT_CRITICAL(&xTaskQueueMutex);

	return xAlreadyYielded;
}