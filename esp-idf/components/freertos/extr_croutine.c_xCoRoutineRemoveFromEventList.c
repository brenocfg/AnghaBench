#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ uxPriority; } ;
struct TYPE_3__ {scalar_t__ uxPriority; int /*<<< orphan*/  xEventListItem; } ;
typedef  int /*<<< orphan*/  List_t ;
typedef  TYPE_1__ CRCB_t ;
typedef  int /*<<< orphan*/  BaseType_t ;

/* Variables and functions */
 scalar_t__ listGET_OWNER_OF_HEAD_ENTRY (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  pdFALSE ; 
 int /*<<< orphan*/  pdTRUE ; 
 TYPE_2__* pxCurrentCoRoutine ; 
 int /*<<< orphan*/  uxListRemove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vListInsertEnd (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xPendingReadyCoRoutineList ; 

BaseType_t xCoRoutineRemoveFromEventList( const List_t *pxEventList )
{
CRCB_t *pxUnblockedCRCB;
BaseType_t xReturn;

	/* This function is called from within an interrupt.  It can only access
	event lists and the pending ready list.  This function assumes that a
	check has already been made to ensure pxEventList is not empty. */
	pxUnblockedCRCB = ( CRCB_t * ) listGET_OWNER_OF_HEAD_ENTRY( pxEventList );
	( void ) uxListRemove( &( pxUnblockedCRCB->xEventListItem ) );
	vListInsertEnd( ( List_t * ) &( xPendingReadyCoRoutineList ), &( pxUnblockedCRCB->xEventListItem ) );

	if( pxUnblockedCRCB->uxPriority >= pxCurrentCoRoutine->uxPriority )
	{
		xReturn = pdTRUE;
	}
	else
	{
		xReturn = pdFALSE;
	}

	return xReturn;
}