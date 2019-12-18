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
typedef  int useconds_t ;
struct timespec {int tv_sec; int tv_nsec; } ;
typedef  long DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  Sleep (long) ; 
 int /*<<< orphan*/  TIME_UTC ; 
 scalar_t__ clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 int /*<<< orphan*/  usleep (int) ; 

int thrd_sleep(const struct timespec *time_point, struct timespec *remaining)
{
  struct timespec now;
#if defined(_TTHREAD_WIN32_)
  DWORD delta;
#else
  long delta;
#endif

  /* Get the current time */
  if (clock_gettime(TIME_UTC, &now) != 0)
    return -2;  // FIXME: Some specific error code?

#if defined(_TTHREAD_WIN32_)
  /* Delta in milliseconds */
  delta = (DWORD) ((time_point->tv_sec - now.tv_sec) * 1000 +
                   (time_point->tv_nsec - now.tv_nsec + 500000) / 1000000);
  if (delta > 0)
  {
    Sleep(delta);
  }
#else
  /* Delta in microseconds */
  delta = (time_point->tv_sec - now.tv_sec) * 1000000L +
          (time_point->tv_nsec - now.tv_nsec + 500L) / 1000L;

  /* On some systems, the usleep argument must be < 1000000 */
  while (delta > 999999L)
  {
    usleep(999999);
    delta -= 999999L;
  }
  if (delta > 0L)
  {
    usleep((useconds_t)delta);
  }
#endif

  /* We don't support waking up prematurely (yet) */
  if (remaining)
  {
    remaining->tv_sec = 0;
    remaining->tv_nsec = 0;
  }
  return 0;
}