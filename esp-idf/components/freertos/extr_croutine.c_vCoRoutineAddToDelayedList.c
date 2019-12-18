#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ TickType_t ;
struct TYPE_2__ {int /*<<< orphan*/  xEventListItem; int /*<<< orphan*/  xGenericListItem; } ;
typedef  int /*<<< orphan*/  List_t ;
typedef  int /*<<< orphan*/  ListItem_t ;

/* Variables and functions */
 int /*<<< orphan*/  listSET_LIST_ITEM_VALUE (int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_1__* pxCurrentCoRoutine ; 
 scalar_t__ pxDelayedCoRoutineList ; 
 scalar_t__ pxOverflowDelayedCoRoutineList ; 
 int /*<<< orphan*/  uxListRemove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vListInsert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ xCoRoutineTickCount ; 

void vCoRoutineAddToDelayedList( TickType_t xTicksToDelay, List_t *pxEventList )
{
TickType_t xTimeToWake;

	/* Calculate the time to wake - this may overflow but this is
	not a problem. */
	xTimeToWake = xCoRoutineTickCount + xTicksToDelay;

	/* We must remove ourselves from the ready list before adding
	ourselves to the blocked list as the same list item is used for
	both lists. */
	( void ) uxListRemove( ( ListItem_t * ) &( pxCurrentCoRoutine->xGenericListItem ) );

	/* The list item will be inserted in wake time order. */
	listSET_LIST_ITEM_VALUE( &( pxCurrentCoRoutine->xGenericListItem ), xTimeToWake );

	if( xTimeToWake < xCoRoutineTickCount )
	{
		/* Wake time has overflowed.  Place this item in the
		overflow list. */
		vListInsert( ( List_t * ) pxOverflowDelayedCoRoutineList, ( ListItem_t * ) &( pxCurrentCoRoutine->xGenericListItem ) );
	}
	else
	{
		/* The wake time has not overflowed, so we can use the
		current block list. */
		vListInsert( ( List_t * ) pxDelayedCoRoutineList, ( ListItem_t * ) &( pxCurrentCoRoutine->xGenericListItem ) );
	}

	if( pxEventList )
	{
		/* Also add the co-routine to an event list.  If this is done then the
		function must be called with interrupts disabled. */
		vListInsert( pxEventList, &( pxCurrentCoRoutine->xEventListItem ) );
	}
}