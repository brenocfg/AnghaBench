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
typedef  int const uint32_t ;
typedef  unsigned long portPOINTER_SIZE_TYPE ;
typedef  unsigned int UBaseType_t ;
typedef  scalar_t__ TickType_t ;
typedef  scalar_t__ TaskHandle_t ;
typedef  int /*<<< orphan*/  TaskFunction_t ;
struct TYPE_4__ {char* pcTaskName; unsigned int uxPriority; unsigned int uxBasePriority; unsigned int uxCriticalNesting; unsigned long ulRunTimeCounter; void* pxTopOfStack; void* ucDelayAborted; int /*<<< orphan*/  xNewLib_reent; int /*<<< orphan*/  eNotifyState; scalar_t__ ulNotifiedValue; int /*<<< orphan*/ ** pvThreadLocalStoragePointersDelCallback; int /*<<< orphan*/ ** pvThreadLocalStoragePointers; int /*<<< orphan*/ * pxStack; int /*<<< orphan*/  xMPUSettings; int /*<<< orphan*/ * pxTaskTag; int /*<<< orphan*/  xEventListItem; int /*<<< orphan*/  xGenericListItem; scalar_t__ uxMutexesHeld; void* xCoreID; int /*<<< orphan*/ * pxEndOfStack; } ;
typedef  TYPE_1__ TCB_t ;
typedef  int /*<<< orphan*/  StackType_t ;
typedef  int /*<<< orphan*/  MemoryRegion_t ;
typedef  void* BaseType_t ;

/* Variables and functions */
 int /*<<< orphan*/  configASSERT (int) ; 
 scalar_t__ configMAX_PRIORITIES ; 
 int configMAX_TASK_NAME_LEN ; 
 scalar_t__ configNUM_THREAD_LOCAL_STORAGE_POINTERS ; 
 int /*<<< orphan*/  eNotWaitingNotification ; 
 int /*<<< orphan*/  esp_reent_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listSET_LIST_ITEM_OWNER (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  listSET_LIST_ITEM_VALUE (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,size_t) ; 
 int /*<<< orphan*/  mtCOVERAGE_TEST_MARKER () ; 
 void* pdFALSE ; 
 void* pdTRUE ; 
 scalar_t__ portBYTE_ALIGNMENT_MASK ; 
 unsigned int portPRIVILEGE_BIT ; 
 void* pxPortInitialiseStack (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void* const,...) ; 
 scalar_t__ tskSTACK_FILL_BYTE ; 
 int /*<<< orphan*/  vListInitialiseItem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vPortStoreTaskMPUSettings (int /*<<< orphan*/ *,int /*<<< orphan*/  const* const,int /*<<< orphan*/ *,int const) ; 

__attribute__((used)) static void prvInitialiseNewTask( 	TaskFunction_t pxTaskCode,
									const char * const pcName,
									const uint32_t ulStackDepth,
									void * const pvParameters,
									UBaseType_t uxPriority,
									TaskHandle_t * const pxCreatedTask,
									TCB_t *pxNewTCB,
									const MemoryRegion_t * const xRegions, const BaseType_t xCoreID ) /*lint !e971 Unqualified char types are allowed for strings and single characters only. */
{
StackType_t *pxTopOfStack;
UBaseType_t x;

	#if( portUSING_MPU_WRAPPERS == 1 )
		/* Should the task be created in privileged mode? */
		BaseType_t xRunPrivileged;
		if( ( uxPriority & portPRIVILEGE_BIT ) != 0U )
		{
			xRunPrivileged = pdTRUE;
		}
		else
		{
			xRunPrivileged = pdFALSE;
		}
		uxPriority &= ~portPRIVILEGE_BIT;
	#endif /* portUSING_MPU_WRAPPERS == 1 */

	/* Avoid dependency on memset() if it is not required. */
	#if( ( configCHECK_FOR_STACK_OVERFLOW > 1 ) || ( configUSE_TRACE_FACILITY == 1 ) || ( INCLUDE_uxTaskGetStackHighWaterMark == 1 ) )
	{
		/* Fill the stack with a known value to assist debugging. */
		( void ) memset( pxNewTCB->pxStack, ( int ) tskSTACK_FILL_BYTE, ( size_t ) ulStackDepth * sizeof( StackType_t ) );
	}
	#endif /* ( ( configCHECK_FOR_STACK_OVERFLOW > 1 ) || ( ( configUSE_TRACE_FACILITY == 1 ) || ( INCLUDE_uxTaskGetStackHighWaterMark == 1 ) ) ) */

	/* Calculate the top of stack address.  This depends on whether the stack
	grows from high memory to low (as per the 80x86) or vice versa.
	portSTACK_GROWTH is used to make the result positive or negative as required
	by the port. */
	#if( portSTACK_GROWTH < 0 )
	{
		pxTopOfStack = pxNewTCB->pxStack + ( ulStackDepth - ( uint32_t ) 1 );
		pxTopOfStack = ( StackType_t * ) ( ( ( portPOINTER_SIZE_TYPE ) pxTopOfStack ) & ( ~( ( portPOINTER_SIZE_TYPE ) portBYTE_ALIGNMENT_MASK ) ) ); /*lint !e923 MISRA exception.  Avoiding casts between pointers and integers is not practical.  Size differences accounted for using portPOINTER_SIZE_TYPE type. */

		/* Check the alignment of the calculated top of stack is correct. */
		configASSERT( ( ( ( portPOINTER_SIZE_TYPE ) pxTopOfStack & ( portPOINTER_SIZE_TYPE ) portBYTE_ALIGNMENT_MASK ) == 0UL ) );
		#if ( configENABLE_TASK_SNAPSHOT == 1 )
		{
			/* need stack end for core dumps */
			pxNewTCB->pxEndOfStack = pxTopOfStack;
		}
#endif
	}
	#else /* portSTACK_GROWTH */
	{
		pxTopOfStack = pxNewTCB->pxStack;

		/* Check the alignment of the stack buffer is correct. */
		configASSERT( ( ( ( portPOINTER_SIZE_TYPE ) pxNewTCB->pxStack & ( portPOINTER_SIZE_TYPE ) portBYTE_ALIGNMENT_MASK ) == 0UL ) );

		/* The other extreme of the stack space is required if stack checking is
		performed. */
		pxNewTCB->pxEndOfStack = pxNewTCB->pxStack + ( ulStackDepth - ( uint32_t ) 1 );
	}
	#endif /* portSTACK_GROWTH */

	/* Store the task name in the TCB. */
	for( x = ( UBaseType_t ) 0; x < ( UBaseType_t ) configMAX_TASK_NAME_LEN; x++ )
	{
		pxNewTCB->pcTaskName[ x ] = pcName[ x ];

		/* Don't copy all configMAX_TASK_NAME_LEN if the string is shorter than
		configMAX_TASK_NAME_LEN characters just in case the memory after the
		string is not accessible (extremely unlikely). */
		if( pcName[ x ] == 0x00 )
		{
			break;
		}
		else
		{
			mtCOVERAGE_TEST_MARKER();
		}
	}

	/* Ensure the name string is terminated in the case that the string length
	was greater or equal to configMAX_TASK_NAME_LEN. */
	pxNewTCB->pcTaskName[ configMAX_TASK_NAME_LEN - 1 ] = '\0';

	/* This is used as an array index so must ensure it's not too large.  First
	remove the privilege bit if one is present. */
	if( uxPriority >= ( UBaseType_t ) configMAX_PRIORITIES )
	{
		uxPriority = ( UBaseType_t ) configMAX_PRIORITIES - ( UBaseType_t ) 1U;
	}
	else
	{
		mtCOVERAGE_TEST_MARKER();
	}

	pxNewTCB->uxPriority = uxPriority;
	pxNewTCB->xCoreID = xCoreID;
	#if ( configUSE_MUTEXES == 1 )
	{
		pxNewTCB->uxBasePriority = uxPriority;
		pxNewTCB->uxMutexesHeld = 0;
	}
	#endif /* configUSE_MUTEXES */

	vListInitialiseItem( &( pxNewTCB->xGenericListItem ) );
	vListInitialiseItem( &( pxNewTCB->xEventListItem ) );

	/* Set the pxNewTCB as a link back from the ListItem_t.  This is so we can get
	back to	the containing TCB from a generic item in a list. */
	listSET_LIST_ITEM_OWNER( &( pxNewTCB->xGenericListItem ), pxNewTCB );

	/* Event lists are always in priority order. */
	listSET_LIST_ITEM_VALUE( &( pxNewTCB->xEventListItem ), ( TickType_t ) configMAX_PRIORITIES - ( TickType_t ) uxPriority ); /*lint !e961 MISRA exception as the casts are only redundant for some ports. */
	listSET_LIST_ITEM_OWNER( &( pxNewTCB->xEventListItem ), pxNewTCB );

	#if ( portCRITICAL_NESTING_IN_TCB == 1 )
	{
		pxNewTCB->uxCriticalNesting = ( UBaseType_t ) 0U;
	}
	#endif /* portCRITICAL_NESTING_IN_TCB */

	#if ( configUSE_APPLICATION_TASK_TAG == 1 )
	{
		pxNewTCB->pxTaskTag = NULL;
	}
	#endif /* configUSE_APPLICATION_TASK_TAG */

	#if ( configGENERATE_RUN_TIME_STATS == 1 )
	{
		pxNewTCB->ulRunTimeCounter = 0UL;
	}
	#endif /* configGENERATE_RUN_TIME_STATS */

	#if ( portUSING_MPU_WRAPPERS == 1 )
	{
		vPortStoreTaskMPUSettings( &( pxNewTCB->xMPUSettings ), xRegions, pxNewTCB->pxStack, ulStackDepth );
	}
	#else
	{
		/* Avoid compiler warning about unreferenced parameter. */
		( void ) xRegions;
	}
	#endif

	#if( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 )
	{
		for( x = 0; x < ( UBaseType_t ) configNUM_THREAD_LOCAL_STORAGE_POINTERS; x++ )
		{
			pxNewTCB->pvThreadLocalStoragePointers[ x ] = NULL;
			#if ( configTHREAD_LOCAL_STORAGE_DELETE_CALLBACKS == 1)
			pxNewTCB->pvThreadLocalStoragePointersDelCallback[ x ] = NULL;
			#endif
		}
	}
	#endif

	#if ( configUSE_TASK_NOTIFICATIONS == 1 )
	{
		pxNewTCB->ulNotifiedValue = 0;
		pxNewTCB->eNotifyState = eNotWaitingNotification;
	}
	#endif

	#if ( configUSE_NEWLIB_REENTRANT == 1 )
	{
		/* Initialise this task's Newlib reent structure. */
		esp_reent_init(&pxNewTCB->xNewLib_reent);
	}
	#endif

	#if( INCLUDE_xTaskAbortDelay == 1 )
	{
		pxNewTCB->ucDelayAborted = pdFALSE;
	}
	#endif

	/* Initialize the TCB stack to look as if the task was already running,
	but had been interrupted by the scheduler.  The return address is set
	to the start of the task function. Once the stack has been initialised
	the	top of stack variable is updated. */
	#if( portUSING_MPU_WRAPPERS == 1 )
	{
		pxNewTCB->pxTopOfStack = pxPortInitialiseStack( pxTopOfStack, pxTaskCode, pvParameters, xRunPrivileged );
	}
	#else /* portUSING_MPU_WRAPPERS */
	{
		pxNewTCB->pxTopOfStack = pxPortInitialiseStack( pxTopOfStack, pxTaskCode, pvParameters );
	}
	#endif /* portUSING_MPU_WRAPPERS */

	if( ( void * ) pxCreatedTask != NULL )
	{
		/* Pass the handle out in an anonymous way.  The handle can be used to
		change the created task's priority, delete the created task, etc.*/
		*pxCreatedTask = ( TaskHandle_t ) pxNewTCB;
	}
	else
	{
		mtCOVERAGE_TEST_MARKER();
	}
}