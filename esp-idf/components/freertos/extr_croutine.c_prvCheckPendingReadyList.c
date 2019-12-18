#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  xGenericListItem; int /*<<< orphan*/  xEventListItem; } ;
typedef  TYPE_1__ CRCB_t ;

/* Variables and functions */
 scalar_t__ listGET_OWNER_OF_HEAD_ENTRY (int /*<<< orphan*/ *) ; 
 scalar_t__ listLIST_IS_EMPTY (int /*<<< orphan*/ *) ; 
 scalar_t__ pdFALSE ; 
 int /*<<< orphan*/  portDISABLE_INTERRUPTS () ; 
 int /*<<< orphan*/  portENABLE_INTERRUPTS () ; 
 int /*<<< orphan*/  prvAddCoRoutineToReadyQueue (TYPE_1__*) ; 
 int /*<<< orphan*/  uxListRemove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xPendingReadyCoRoutineList ; 

__attribute__((used)) static void prvCheckPendingReadyList( void )
{
	/* Are there any co-routines waiting to get moved to the ready list?  These
	are co-routines that have been readied by an ISR.  The ISR cannot access
	the	ready lists itself. */
	while( listLIST_IS_EMPTY( &xPendingReadyCoRoutineList ) == pdFALSE )
	{
		CRCB_t *pxUnblockedCRCB;

		/* The pending ready list can be accessed by an ISR. */
		portDISABLE_INTERRUPTS();
		{
			pxUnblockedCRCB = ( CRCB_t * ) listGET_OWNER_OF_HEAD_ENTRY( (&xPendingReadyCoRoutineList) );
			( void ) uxListRemove( &( pxUnblockedCRCB->xEventListItem ) );
		}
		portENABLE_INTERRUPTS();

		( void ) uxListRemove( &( pxUnblockedCRCB->xGenericListItem ) );
		prvAddCoRoutineToReadyQueue( pxUnblockedCRCB );
	}
}