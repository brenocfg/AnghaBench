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
typedef  scalar_t__ UINT ;

/* Variables and functions */
 scalar_t__ Tick () ; 
 scalar_t__ TickRealtimeManual () ; 

UINT TickRealtime()
{
#if	defined(OS_WIN32) || defined(CLOCK_REALTIME) || defined(CLOCK_MONOTONIC) || defined(CLOCK_HIGHRES) || defined(UNIX_MACOS)
	return Tick() + 1;
#else
	return TickRealtimeManual() + 1;
#endif
}