#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  uxIndex; int /*<<< orphan*/  (* pxCoRoutineFunction ) (TYPE_1__*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  listGET_OWNER_OF_NEXT_ENTRY (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ listLIST_IS_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prvCheckDelayedList () ; 
 int /*<<< orphan*/  prvCheckPendingReadyList () ; 
 TYPE_1__* pxCurrentCoRoutine ; 
 int /*<<< orphan*/ * pxReadyCoRoutineLists ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 size_t uxTopCoRoutineReadyPriority ; 

void vCoRoutineSchedule( void )
{
	/* See if any co-routines readied by events need moving to the ready lists. */
	prvCheckPendingReadyList();

	/* See if any delayed co-routines have timed out. */
	prvCheckDelayedList();

	/* Find the highest priority queue that contains ready co-routines. */
	while( listLIST_IS_EMPTY( &( pxReadyCoRoutineLists[ uxTopCoRoutineReadyPriority ] ) ) )
	{
		if( uxTopCoRoutineReadyPriority == 0 )
		{
			/* No more co-routines to check. */
			return;
		}
		--uxTopCoRoutineReadyPriority;
	}

	/* listGET_OWNER_OF_NEXT_ENTRY walks through the list, so the co-routines
	 of the	same priority get an equal share of the processor time. */
	listGET_OWNER_OF_NEXT_ENTRY( pxCurrentCoRoutine, &( pxReadyCoRoutineLists[ uxTopCoRoutineReadyPriority ] ) );

	/* Call the co-routine. */
	( pxCurrentCoRoutine->pxCoRoutineFunction )( pxCurrentCoRoutine, pxCurrentCoRoutine->uxIndex );

	return;
}