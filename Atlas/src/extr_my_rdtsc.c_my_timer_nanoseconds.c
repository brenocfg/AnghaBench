#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int ulonglong ;
struct TYPE_5__ {scalar_t__ tb_low; scalar_t__ tb_high; } ;
typedef  TYPE_1__ timebasestruct_t ;
struct timespec {scalar_t__ tv_nsec; scalar_t__ tv_sec; } ;
struct TYPE_6__ {int denom; int numer; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ mach_timebase_info_data_t ;
typedef  scalar_t__ NXTime_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_REALTIME ; 
 int /*<<< orphan*/  NXGetTime (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  NX_NSECONDS ; 
 int /*<<< orphan*/  NX_SINCE_1970 ; 
 int /*<<< orphan*/  TIMEBASE_SZ ; 
 int /*<<< orphan*/  clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 scalar_t__ gethrtime () ; 
 int mach_absolute_time () ; 
 int /*<<< orphan*/  mach_timebase_info (TYPE_2__*) ; 
 int /*<<< orphan*/  read_real_time (TYPE_1__*,int /*<<< orphan*/ ) ; 

ulonglong my_timer_nanoseconds(void)
{
#if defined(HAVE_READ_REAL_TIME)
  {
    timebasestruct_t tr;
    read_real_time(&tr, TIMEBASE_SZ);
    return (ulonglong) tr.tb_high * 1000000000 + (ulonglong) tr.tb_low;
  }
#elif defined(HAVE_CLOCK_GETTIME) && defined(CLOCK_REALTIME)
  {
    struct timespec tp;
    clock_gettime(CLOCK_REALTIME, &tp);
    return (ulonglong) tp.tv_sec * 1000000000 + (ulonglong) tp.tv_nsec;
  }
#elif defined(HAVE_SYS_TIMES_H) && defined(HAVE_GETHRTIME)
  /* SunOS 5.10+, Solaris, HP-UX: hrtime_t gethrtime(void) */
  return (ulonglong) gethrtime();
#elif defined(__NETWARE__)
  {
    NXTime_t tm;
    NXGetTime(NX_SINCE_1970, NX_NSECONDS, &tm);
    return (ulonglong) tm;
  }
#elif defined(__APPLE__) && defined(__MACH__)
  {
    ulonglong tm;
    static mach_timebase_info_data_t timebase_info= {0,0};
    if (timebase_info.denom == 0)
      (void) mach_timebase_info(&timebase_info);
    tm= mach_absolute_time();
    return (tm * timebase_info.numer) / timebase_info.denom;
  }
#else
  return 0;
#endif
}