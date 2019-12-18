#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int ulonglong ;
struct timeb {scalar_t__ millitm; scalar_t__ time; } ;
struct TYPE_3__ {scalar_t__ dwHighDateTime; scalar_t__ dwLowDateTime; } ;
typedef  scalar_t__ NXTime_t ;
typedef  TYPE_1__ FILETIME ;

/* Variables and functions */
 int /*<<< orphan*/  GetSystemTimeAsFileTime (TYPE_1__*) ; 
 int /*<<< orphan*/  NXGetTime (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  NX_MSECONDS ; 
 int /*<<< orphan*/  NX_SINCE_1970 ; 
 int /*<<< orphan*/  ftime (struct timeb*) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

ulonglong my_timer_milliseconds(void)
{
#if defined(HAVE_SYS_TIMEB_H) && defined(HAVE_FTIME)
  /* ftime() is obsolete but maybe the platform is old */
  struct timeb ft;
  ftime(&ft);
  return (ulonglong)ft.time * 1000 + (ulonglong)ft.millitm;
#elif defined(HAVE_TIME)
  return (ulonglong) time(NULL) * 1000;
#elif defined(_WIN32)
   FILETIME ft;
   GetSystemTimeAsFileTime( &ft );
   return ((ulonglong)ft.dwLowDateTime +
                  (((ulonglong)ft.dwHighDateTime) << 32))/10000;
#elif defined(__NETWARE__)
  {
    NXTime_t tm;
    NXGetTime(NX_SINCE_1970, NX_MSECONDS, &tm);
    return (ulonglong)tm;
  }
#else
  return 0;
#endif
}