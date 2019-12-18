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
 int /*<<< orphan*/  EINVAL ; 
 int PTW32_MIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SCHED_MAX ; 
 int SCHED_MIN ; 
 int /*<<< orphan*/  THREAD_PRIORITY_IDLE ; 
 int /*<<< orphan*/  THREAD_PRIORITY_TIME_CRITICAL ; 
 int /*<<< orphan*/  errno ; 

int
sched_get_priority_min (int policy)
{
  if (policy < SCHED_MIN || policy > SCHED_MAX)
    {
      errno = EINVAL;
      return -1;
    }

#if (THREAD_PRIORITY_LOWEST > THREAD_PRIORITY_NORMAL)
  /* WinCE? */
  return PTW32_MIN (THREAD_PRIORITY_IDLE, THREAD_PRIORITY_TIME_CRITICAL);
#else
  /* This is independent of scheduling policy in Win32. */
  return PTW32_MIN (THREAD_PRIORITY_IDLE, THREAD_PRIORITY_TIME_CRITICAL);
#endif
}