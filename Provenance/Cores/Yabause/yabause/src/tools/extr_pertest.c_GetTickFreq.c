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
typedef  int u64 ;
typedef  int /*<<< orphan*/  LARGE_INTEGER ;

/* Variables and functions */
 int /*<<< orphan*/  QueryPerformanceFrequency (int /*<<< orphan*/ *) ; 
 int secs_to_ticks (int) ; 

u64 GetTickFreq() 
{
	u64 tickfreq;
#ifdef WIN32
	QueryPerformanceFrequency((LARGE_INTEGER *)&tickfreq);
#elif defined(_arch_dreamcast)
	tickfreq = 1000;
#elif defined(GEKKO)
	tickfreq = secs_to_ticks(1);
#elif defined(PSP)
	tickfreq = 1000000;
#elif defined(HAVE_GETTIMEOFDAY)
	tickfreq = 1000000;
#elif defined(HAVE_LIBSDL)
	tickfreq = 1000;
#endif
	return tickfreq;
}