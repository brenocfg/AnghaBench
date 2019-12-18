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
typedef  scalar_t__ BaseType_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYSTICK_INTR_ID ; 
 scalar_t__ pdFALSE ; 
 int /*<<< orphan*/  portYIELD_FROM_ISR () ; 
 int /*<<< orphan*/  portbenchmarkIntLatency () ; 
 int /*<<< orphan*/  traceISR_ENTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  traceISR_EXIT () ; 
 scalar_t__ xTaskIncrementTick () ; 

BaseType_t xPortSysTickHandler( void )
{
	BaseType_t ret;

	portbenchmarkIntLatency();
	traceISR_ENTER(SYSTICK_INTR_ID);
	ret = xTaskIncrementTick();
	if( ret != pdFALSE )
	{
		portYIELD_FROM_ISR();
	} else {
		traceISR_EXIT();
	}
	return ret;
}