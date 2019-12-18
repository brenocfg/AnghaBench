#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int sys_time_sec_t ;
typedef  int sys_time_nsec_t ;
struct timeval {int tv_sec; int tv_usec; } ;
struct timespec {int tv_sec; int tv_nsec; int /*<<< orphan*/  member_0; } ;
struct TYPE_9__ {int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ slock_t ;
struct TYPE_10__ {int /*<<< orphan*/  cond; } ;
typedef  TYPE_2__ scond_t ;
struct TYPE_11__ {int tv_sec; int tv_nsec; } ;
typedef  TYPE_3__ mach_timespec_t ;
typedef  int int64_t ;
typedef  int /*<<< orphan*/  clock_serv_t ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CALENDAR_CLOCK ; 
 int /*<<< orphan*/  CLOCK_REALTIME ; 
 int INT64_C (int) ; 
 int /*<<< orphan*/  _ftime64_s (struct timespec*) ; 
 int _scond_wait_win32 (TYPE_2__*,TYPE_1__*,int) ; 
 int clock () ; 
 int /*<<< orphan*/  clock_get_time (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  host_get_clock_service (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mach_host_self () ; 
 int /*<<< orphan*/  mach_port_deallocate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mach_task_self () ; 
 int pthread_cond_timedwait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timespec*) ; 
 int /*<<< orphan*/  sys_time_get_current_time (int*,int*) ; 

bool scond_wait_timeout(scond_t *cond, slock_t *lock, int64_t timeout_us)
{
#ifdef USE_WIN32_THREADS
   /* How to convert a microsecond (us) timeout to millisecond (ms)?
    *
    * Someone asking for a 0 timeout clearly wants immediate timeout.
    * Someone asking for a 1 timeout clearly wants an actual timeout
    * of the minimum length */

   /* Someone asking for 1000 or 1001 timeout shouldn't
    * accidentally get 2ms. */
   DWORD dwMilliseconds = timeout_us/1000;

   /* The implementation of a 0 timeout here with pthreads is sketchy.
    * It isn't clear what happens if pthread_cond_timedwait is called with NOW.
    * Moreover, it is possible that this thread gets pre-empted after the
    * clock_gettime but before the pthread_cond_timedwait.
    * In order to help smoke out problems caused by this strange usage,
    * let's treat a 0 timeout as always timing out.
    */
   if (timeout_us == 0)
      return false;
   else if (timeout_us < 1000)
      dwMilliseconds = 1;

   return _scond_wait_win32(cond,lock,dwMilliseconds);
#else
   int ret;
   int64_t seconds, remainder;
   struct timespec now = {0};

#ifdef __MACH__
   /* OSX doesn't have clock_gettime. */
   clock_serv_t cclock;
   mach_timespec_t mts;

   host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);
   clock_get_time(cclock, &mts);
   mach_port_deallocate(mach_task_self(), cclock);
   now.tv_sec = mts.tv_sec;
   now.tv_nsec = mts.tv_nsec;
#elif defined(__CELLOS_LV2__)
   sys_time_sec_t s;
   sys_time_nsec_t n;

   sys_time_get_current_time(&s, &n);
   now.tv_sec  = s;
   now.tv_nsec = n;
#elif defined(PS2)
   int tickms = clock();
   now.tv_sec = tickms/1000;
   now.tv_nsec = tickms * 1000;
#elif defined(__mips__) || defined(VITA) || defined(_3DS)
   struct timeval tm;

   gettimeofday(&tm, NULL);
   now.tv_sec = tm.tv_sec;
   now.tv_nsec = tm.tv_usec * 1000;
#elif defined(RETRO_WIN32_USE_PTHREADS)
   _ftime64_s(&now);
#elif !defined(GEKKO)
   /* timeout on libogc is duration, not end time. */
   clock_gettime(CLOCK_REALTIME, &now);
#endif

   seconds      = timeout_us / INT64_C(1000000);
   remainder    = timeout_us % INT64_C(1000000);

   now.tv_sec  += seconds;
   now.tv_nsec += remainder * INT64_C(1000);

   if (now.tv_nsec > 1000000000)
   {
      now.tv_nsec -= 1000000000;
      now.tv_sec += 1;
   }

   ret = pthread_cond_timedwait(&cond->cond, &lock->lock, &now);
   return (ret == 0);
#endif
}