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
struct timespec {int tv_sec; int tv_nsec; } ;
typedef  int /*<<< orphan*/  mtx_t ;
typedef  int /*<<< orphan*/  cnd_t ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  TIME_UTC ; 
 int _cnd_timedwait_win32 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 int pthread_cond_timedwait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timespec const*) ; 
 int thrd_error ; 
 int thrd_success ; 
 int thrd_timeout ; 

int cnd_timedwait(cnd_t *cond, mtx_t *mtx, const struct timespec *ts)
{
#if defined(_TTHREAD_WIN32_)
  struct timespec now;
  if (clock_gettime(TIME_UTC, &now) == 0)
  {
    DWORD delta = (DWORD) ((ts->tv_sec - now.tv_sec) * 1000 +
                           (ts->tv_nsec - now.tv_nsec + 500000) / 1000000);
    return _cnd_timedwait_win32(cond, mtx, delta);
  }
  else
    return thrd_error;
#else
  int ret;
  ret = pthread_cond_timedwait(cond, mtx, ts);
  if (ret == ETIMEDOUT)
  {
    return thrd_timeout;
  }
  return ret == 0 ? thrd_success : thrd_error;
#endif
}