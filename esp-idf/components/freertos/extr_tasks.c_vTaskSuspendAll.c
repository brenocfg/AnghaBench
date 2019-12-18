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

/* Variables and functions */
 unsigned int portENTER_CRITICAL_NESTED () ; 
 int /*<<< orphan*/  portEXIT_CRITICAL_NESTED (unsigned int) ; 
 int /*<<< orphan*/ * uxSchedulerSuspended ; 
 size_t xPortGetCoreID () ; 

void vTaskSuspendAll( void )
{
	/* A critical section is not required as the variable is of type
	BaseType_t.  Please read Richard Barry's reply in the following link to a
	post in the FreeRTOS support forum before reporting this as a bug! -
	http://goo.gl/wu4acr */
	unsigned state;

	state = portENTER_CRITICAL_NESTED();
	++uxSchedulerSuspended[ xPortGetCoreID() ];
	portEXIT_CRITICAL_NESTED(state);
}