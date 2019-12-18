#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UBaseType_t ;
struct TYPE_5__ {int xCoreID; } ;
typedef  TYPE_1__ TCB_t ;
typedef  int /*<<< orphan*/  ListItem_t ;
typedef  scalar_t__ BaseType_t ;

/* Variables and functions */
 int /*<<< orphan*/ * listGET_END_MARKER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * listGET_HEAD_ENTRY (int /*<<< orphan*/ *) ; 
 scalar_t__ listGET_LIST_ITEM_OWNER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * listGET_NEXT (int /*<<< orphan*/ *) ; 
 scalar_t__ listLIST_IS_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtCOVERAGE_TEST_MARKER () ; 
 scalar_t__ pdFALSE ; 
 int portNUM_PROCESSORS ; 
 int /*<<< orphan*/  prvDeleteTCB (TYPE_1__*) ; 
 int /*<<< orphan*/  prvDeleteTLS (TYPE_1__*) ; 
 TYPE_1__** pxCurrentTCB ; 
 int /*<<< orphan*/  taskENTER_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskEXIT_CRITICAL (int /*<<< orphan*/ *) ; 
 int tskNO_AFFINITY ; 
 int /*<<< orphan*/  uxCurrentNumberOfTasks ; 
 int /*<<< orphan*/  uxListRemove (int /*<<< orphan*/ *) ; 
 scalar_t__ uxTasksDeleted ; 
 int xPortGetCoreID () ; 
 int /*<<< orphan*/  xTaskQueueMutex ; 
 int /*<<< orphan*/  xTasksWaitingTermination ; 

__attribute__((used)) static void prvCheckTasksWaitingTermination( void )
{
	#if ( INCLUDE_vTaskDelete == 1 )
	{
		BaseType_t xListIsEmpty;
		int core = xPortGetCoreID();

		/* ucTasksDeleted is used to prevent vTaskSuspendAll() being called
		too often in the idle task. */
		while(uxTasksDeleted > ( UBaseType_t ) 0U )
		{
			TCB_t *pxTCB = NULL;

			taskENTER_CRITICAL(&xTaskQueueMutex);
			{
				xListIsEmpty = listLIST_IS_EMPTY( &xTasksWaitingTermination );
				if( xListIsEmpty == pdFALSE )
				{
					/* We only want to kill tasks that ran on this core because e.g. _xt_coproc_release needs to
					be called on the core the process is pinned on, if any */
					ListItem_t *target = listGET_HEAD_ENTRY(&xTasksWaitingTermination);
					for( ; target != listGET_END_MARKER(&xTasksWaitingTermination); target = listGET_NEXT(target) ){	//Walk the list
						TCB_t *tgt_tcb = ( TCB_t * )listGET_LIST_ITEM_OWNER(target);
						int affinity = tgt_tcb->xCoreID;
						//Self deleting tasks are added to Termination List before they switch context. Ensure they aren't still currently running
						if( pxCurrentTCB[core] == tgt_tcb || (portNUM_PROCESSORS > 1 && pxCurrentTCB[!core] == tgt_tcb) ){
							continue;	//Can't free memory of task that is still running
						}
						if(affinity == core || affinity == tskNO_AFFINITY){		//Find first item not pinned to other core
							pxTCB = tgt_tcb;
							break;
						}
					}
					if(pxTCB != NULL){
						( void ) uxListRemove( target );	//Remove list item from list
						--uxCurrentNumberOfTasks;
						--uxTasksDeleted;
					}
				}
			}
			taskEXIT_CRITICAL(&xTaskQueueMutex);	//Need to call deletion callbacks outside critical section

			if (pxTCB != NULL) {	//Call deletion callbacks and free TCB memory
				#if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS > 0 ) && ( configTHREAD_LOCAL_STORAGE_DELETE_CALLBACKS )
					prvDeleteTLS( pxTCB );
				#endif
				prvDeleteTCB( pxTCB );
			}
			else
			{
				mtCOVERAGE_TEST_MARKER();
				break;	//No TCB found that could be freed by this core, break out of loop
			}
		}
	}
	#endif /* vTaskDelete */
}