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
typedef  int BaseType_t ;

/* Variables and functions */
 unsigned int portENTER_CRITICAL_NESTED () ; 
 int /*<<< orphan*/  portEXIT_CRITICAL_NESTED (unsigned int) ; 
 scalar_t__* port_interruptNesting ; 
 size_t xPortGetCoreID () ; 

BaseType_t xPortInIsrContext(void)
{
	unsigned int irqStatus;
	BaseType_t ret;
	irqStatus=portENTER_CRITICAL_NESTED();
	ret=(port_interruptNesting[xPortGetCoreID()] != 0);
	portEXIT_CRITICAL_NESTED(irqStatus);
	return ret;
}