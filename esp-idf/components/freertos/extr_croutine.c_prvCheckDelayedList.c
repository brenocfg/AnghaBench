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
struct TYPE_6__ {scalar_t__ pvContainer; } ;
struct TYPE_5__ {TYPE_2__ xEventListItem; TYPE_2__ xGenericListItem; } ;
typedef  int /*<<< orphan*/  List_t ;
typedef  TYPE_1__ CRCB_t ;

/* Variables and functions */
 scalar_t__ listGET_LIST_ITEM_VALUE (TYPE_2__*) ; 
 scalar_t__ listGET_OWNER_OF_HEAD_ENTRY (int /*<<< orphan*/ *) ; 
 scalar_t__ listLIST_IS_EMPTY (int /*<<< orphan*/ *) ; 
 scalar_t__ pdFALSE ; 
 int /*<<< orphan*/  portDISABLE_INTERRUPTS () ; 
 int /*<<< orphan*/  portENABLE_INTERRUPTS () ; 
 int /*<<< orphan*/  prvAddCoRoutineToReadyQueue (TYPE_1__*) ; 
 int /*<<< orphan*/ * pxDelayedCoRoutineList ; 
 int /*<<< orphan*/ * pxOverflowDelayedCoRoutineList ; 
 int /*<<< orphan*/  uxListRemove (TYPE_2__*) ; 
 scalar_t__ xCoRoutineTickCount ; 
 scalar_t__ xLastTickCount ; 
 scalar_t__ xPassedTicks ; 
 scalar_t__ xTaskGetTickCount () ; 

__attribute__((used)) static void prvCheckDelayedList( void )
{
CRCB_t *pxCRCB;

	xPassedTicks = xTaskGetTickCount() - xLastTickCount;
	while( xPassedTicks )
	{
		xCoRoutineTickCount++;
		xPassedTicks--;

		/* If the tick count has overflowed we need to swap the ready lists. */
		if( xCoRoutineTickCount == 0 )
		{
			List_t * pxTemp;

			/* Tick count has overflowed so we need to swap the delay lists.  If there are
			any items in pxDelayedCoRoutineList here then there is an error! */
			pxTemp = pxDelayedCoRoutineList;
			pxDelayedCoRoutineList = pxOverflowDelayedCoRoutineList;
			pxOverflowDelayedCoRoutineList = pxTemp;
		}

		/* See if this tick has made a timeout expire. */
		while( listLIST_IS_EMPTY( pxDelayedCoRoutineList ) == pdFALSE )
		{
			pxCRCB = ( CRCB_t * ) listGET_OWNER_OF_HEAD_ENTRY( pxDelayedCoRoutineList );

			if( xCoRoutineTickCount < listGET_LIST_ITEM_VALUE( &( pxCRCB->xGenericListItem ) ) )
			{
				/* Timeout not yet expired. */
				break;
			}

			portDISABLE_INTERRUPTS();
			{
				/* The event could have occurred just before this critical
				section.  If this is the case then the generic list item will
				have been moved to the pending ready list and the following
				line is still valid.  Also the pvContainer parameter will have
				been set to NULL so the following lines are also valid. */
				( void ) uxListRemove( &( pxCRCB->xGenericListItem ) );

				/* Is the co-routine waiting on an event also? */
				if( pxCRCB->xEventListItem.pvContainer )
				{
					( void ) uxListRemove( &( pxCRCB->xEventListItem ) );
				}
			}
			portENABLE_INTERRUPTS();

			prvAddCoRoutineToReadyQueue( pxCRCB );
		}
	}

	xLastTickCount = xCoRoutineTickCount;
}