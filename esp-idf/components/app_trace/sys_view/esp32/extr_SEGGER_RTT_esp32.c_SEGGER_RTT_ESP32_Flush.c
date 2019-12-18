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
 int /*<<< orphan*/  SEGGER_RTT_ESP32_FlushNoLock (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  SEGGER_SYSVIEW_LOCK () ; 
 int /*<<< orphan*/  SEGGER_SYSVIEW_UNLOCK () ; 

void SEGGER_RTT_ESP32_Flush(unsigned long min_sz, unsigned long tmo)
{
    SEGGER_SYSVIEW_LOCK();
    SEGGER_RTT_ESP32_FlushNoLock(min_sz, tmo);
    SEGGER_SYSVIEW_UNLOCK();
}