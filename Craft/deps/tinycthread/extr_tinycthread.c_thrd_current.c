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
typedef  int /*<<< orphan*/  thrd_t ;

/* Variables and functions */
 int /*<<< orphan*/  GetCurrentThread () ; 
 int /*<<< orphan*/  pthread_self () ; 

thrd_t thrd_current(void)
{
#if defined(_TTHREAD_WIN32_)
  return GetCurrentThread();
#else
  return pthread_self();
#endif
}