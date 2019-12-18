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
typedef  size_t UBaseType_t ;
typedef  int /*<<< orphan*/  List_t ;

/* Variables and functions */
 size_t configMAX_CO_ROUTINE_PRIORITIES ; 
 int /*<<< orphan*/ * pxDelayedCoRoutineList ; 
 int /*<<< orphan*/ * pxOverflowDelayedCoRoutineList ; 
 int /*<<< orphan*/ * pxReadyCoRoutineLists ; 
 int /*<<< orphan*/  vListInitialise (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xDelayedCoRoutineList1 ; 
 int /*<<< orphan*/  xDelayedCoRoutineList2 ; 
 int /*<<< orphan*/  xPendingReadyCoRoutineList ; 

__attribute__((used)) static void prvInitialiseCoRoutineLists( void )
{
UBaseType_t uxPriority;

	for( uxPriority = 0; uxPriority < configMAX_CO_ROUTINE_PRIORITIES; uxPriority++ )
	{
		vListInitialise( ( List_t * ) &( pxReadyCoRoutineLists[ uxPriority ] ) );
	}

	vListInitialise( ( List_t * ) &xDelayedCoRoutineList1 );
	vListInitialise( ( List_t * ) &xDelayedCoRoutineList2 );
	vListInitialise( ( List_t * ) &xPendingReadyCoRoutineList );

	/* Start with pxDelayedCoRoutineList using list1 and the
	pxOverflowDelayedCoRoutineList using list2. */
	pxDelayedCoRoutineList = &xDelayedCoRoutineList1;
	pxOverflowDelayedCoRoutineList = &xDelayedCoRoutineList2;
}