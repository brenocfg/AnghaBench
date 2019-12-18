#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct TYPE_6__ {scalar_t__ ucStaticallyAllocated; } ;
typedef  TYPE_1__ Queue_t ;
typedef  scalar_t__ QueueHandle_t ;

/* Variables and functions */
 int /*<<< orphan*/  configASSERT (TYPE_1__* const) ; 
 int /*<<< orphan*/  mtCOVERAGE_TEST_MARKER () ; 
 scalar_t__ pdFALSE ; 
 int /*<<< orphan*/  traceQUEUE_DELETE (TYPE_1__* const) ; 
 int /*<<< orphan*/  vPortFree (TYPE_1__* const) ; 
 int /*<<< orphan*/  vQueueUnregisterQueue (TYPE_1__* const) ; 

void vQueueDelete( QueueHandle_t xQueue )
{
Queue_t * const pxQueue = ( Queue_t * ) xQueue;

	configASSERT( pxQueue );

	traceQUEUE_DELETE( pxQueue );
	#if ( configQUEUE_REGISTRY_SIZE > 0 )
	{
		vQueueUnregisterQueue( pxQueue );
	}
	#endif

	#if( ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 0 ) )
	{
		/* The queue can only have been allocated dynamically - free it
		again. */
		vPortFree( pxQueue );
	}
	#elif( ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) )
	{
		/* The queue could have been allocated statically or dynamically, so
		check before attempting to free the memory. */
		if( pxQueue->ucStaticallyAllocated == ( uint8_t ) pdFALSE )
		{
			vPortFree( pxQueue );
		}
		else
		{
			mtCOVERAGE_TEST_MARKER();
		}
	}
	#else
	{
		/* The queue must have been statically allocated, so is not going to be
		deleted.  Avoid compiler warnings about the unused parameter. */
		( void ) pxQueue;
	}
	#endif /* configSUPPORT_DYNAMIC_ALLOCATION */
}