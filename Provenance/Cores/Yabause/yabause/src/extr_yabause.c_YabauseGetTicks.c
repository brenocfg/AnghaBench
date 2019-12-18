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
struct timeval {int tv_usec; scalar_t__ tv_sec; } ;
typedef  int /*<<< orphan*/  LARGE_INTEGER ;

/* Variables and functions */
 int /*<<< orphan*/  QueryPerformanceCounter (int /*<<< orphan*/ *) ; 
 scalar_t__ SDL_GetTicks () ; 
 int gettime () ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int sceKernelGetSystemTimeWide () ; 
 scalar_t__ timer_ms_gettime64 () ; 

u64 YabauseGetTicks(void) {
#ifdef WIN32
   u64 ticks;
   QueryPerformanceCounter((LARGE_INTEGER *)&ticks);
   return ticks;
#elif defined(_arch_dreamcast)
   return (u64) timer_ms_gettime64();
#elif defined(GEKKO)
   return gettime();
#elif defined(PSP)
   return sceKernelGetSystemTimeWide();
#elif defined(HAVE_GETTIMEOFDAY)
   struct timeval tv;
   gettimeofday(&tv, NULL);
   return (u64)tv.tv_sec * 1000000 + tv.tv_usec;
#elif defined(HAVE_LIBSDL)
   return (u64)SDL_GetTicks();
#endif
}