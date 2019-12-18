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
typedef  scalar_t__ TickType_t ;
typedef  int BaseType_t ;

/* Variables and functions */
 int /*<<< orphan*/  configASSERT (int) ; 
 int configMAX_TASK_NAME_LEN ; 
 int /*<<< orphan*/  mtCOVERAGE_TEST_MARKER () ; 
 scalar_t__ pdFALSE ; 
 int pdPASS ; 
 int /*<<< orphan*/  pdTRUE ; 
 int /*<<< orphan*/  portCONFIGURE_TIMER_FOR_RUN_TIME_STATS () ; 
 int /*<<< orphan*/  portDISABLE_INTERRUPTS () ; 
 int portNUM_PROCESSORS ; 
 int portPRIVILEGE_BIT ; 
 int /*<<< orphan*/  prvIdleTask ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int tskIDLE_PRIORITY ; 
 int /*<<< orphan*/  tskIDLE_STACK_SIZE ; 
 int /*<<< orphan*/ * xIdleTaskHandle ; 
 scalar_t__ xPortStartScheduler () ; 
 int /*<<< orphan*/  xSchedulerRunning ; 
 int xTaskCreatePinnedToCore (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ *,int) ; 
 scalar_t__ xTickCount ; 
 int xTimerCreateTimerTask () ; 

void vTaskStartScheduler( void )
{
BaseType_t xReturn;
BaseType_t i;

	/* Add the per-core idle tasks at the lowest priority. */
	for ( i=0; i<portNUM_PROCESSORS; i++) {
		//Generate idle task name
		char cIdleName[configMAX_TASK_NAME_LEN];
		snprintf(cIdleName, configMAX_TASK_NAME_LEN, "IDLE%d", i);
		#if ( INCLUDE_xTaskGetIdleTaskHandle == 1 )
		{
			/* Create the idle task, storing its handle in xIdleTaskHandle so it can
			be returned by the xTaskGetIdleTaskHandle() function. */
			xReturn = xTaskCreatePinnedToCore( prvIdleTask, cIdleName, tskIDLE_STACK_SIZE, ( void * ) NULL, ( tskIDLE_PRIORITY | portPRIVILEGE_BIT ), &xIdleTaskHandle[i], i ); /*lint !e961 MISRA exception, justified as it is not a redundant explicit cast to all supported compilers. */
		}
		#else
		{
			/* Create the idle task without storing its handle. */
			xReturn = xTaskCreatePinnedToCore( prvIdleTask, cIdleName, tskIDLE_STACK_SIZE, ( void * ) NULL, ( tskIDLE_PRIORITY | portPRIVILEGE_BIT ), NULL, i);  /*lint !e961 MISRA exception, justified as it is not a redundant explicit cast to all supported compilers. */
		}
		#endif /* INCLUDE_xTaskGetIdleTaskHandle */
	}

	#if ( configUSE_TIMERS == 1 )
	{
		if( xReturn == pdPASS )
		{
			xReturn = xTimerCreateTimerTask();
		}
		else
		{
			mtCOVERAGE_TEST_MARKER();
		}
	}
	#endif /* configUSE_TIMERS */

	if( xReturn == pdPASS )
	{
		/* Interrupts are turned off here, to ensure a tick does not occur
		before or during the call to xPortStartScheduler().  The stacks of
		the created tasks contain a status word with interrupts switched on
		so interrupts will automatically get re-enabled when the first task
		starts to run. */
		portDISABLE_INTERRUPTS();


		xTickCount = ( TickType_t ) 0U;

		/* If configGENERATE_RUN_TIME_STATS is defined then the following
		macro must be defined to configure the timer/counter used to generate
		the run time counter time base. */
		portCONFIGURE_TIMER_FOR_RUN_TIME_STATS();
		xSchedulerRunning = pdTRUE;

		/* Setting up the timer tick is hardware specific and thus in the
		portable interface. */
		if( xPortStartScheduler() != pdFALSE )
		{
			/* Should not reach here as if the scheduler is running the
			function will not return. */
		}
		else
		{
			/* Should only reach here if a task calls xTaskEndScheduler(). */
		}
	}
	else
	{
		/* This line will only be reached if the kernel could not be started,
		because there was not enough FreeRTOS heap to create the idle task
		or the timer task. */
		configASSERT( xReturn );
	}
}