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
struct timeval {scalar_t__ tv_usec; scalar_t__ tv_sec; } ;
struct TYPE_3__ {scalar_t__ QuadPart; } ;
typedef  scalar_t__ NXTime_t ;
typedef  TYPE_1__ LARGE_INTEGER ;

/* Variables and functions */
 int /*<<< orphan*/  NXGetTime (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  NX_SINCE_1970 ; 
 int /*<<< orphan*/  NX_USECONDS ; 
 int /*<<< orphan*/  QueryPerformanceCounter (TYPE_1__*) ; 
 scalar_t__ gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 

ulonglong my_timer_microseconds(void)
{
#if defined(HAVE_GETTIMEOFDAY)
  {
    static ulonglong last_value= 0;
    struct timeval tv;
    if (gettimeofday(&tv, NULL) == 0)
      last_value= (ulonglong) tv.tv_sec * 1000000 + (ulonglong) tv.tv_usec;
    else
    {
      /*
        There are reports that gettimeofday(2) can have intermittent failures
        on some platform, see for example Bug#36819.
        We are not trying again or looping, just returning the best value possible
        under the circumstances ...
      */
      last_value++;
    }
    return last_value;
  }
#elif defined(_WIN32)
  {
    /* QueryPerformanceCounter usually works with about 1/3 microsecond. */
    LARGE_INTEGER t_cnt;

    QueryPerformanceCounter(&t_cnt);
    return (ulonglong) t_cnt.QuadPart;
  }
#elif defined(__NETWARE__)
  {
    NXTime_t tm;
    NXGetTime(NX_SINCE_1970, NX_USECONDS, &tm);
    return (ulonglong) tm;
  }
#else
  return 0;
#endif
}