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
 int /*<<< orphan*/  GetCurrentThreadId () ; 
 int /*<<< orphan*/  pthread_self () ; 

uintptr_t sthread_get_current_thread_id(void)
{
#ifdef USE_WIN32_THREADS
   return (uintptr_t)GetCurrentThreadId();
#else
   return (uintptr_t)pthread_self();
#endif
}