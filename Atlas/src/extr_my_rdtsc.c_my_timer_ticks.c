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
typedef  int /*<<< orphan*/  ulonglong ;
struct tms {int dummy; } ;
typedef  int /*<<< orphan*/  NXTime_t ;

/* Variables and functions */
 int /*<<< orphan*/  GetTickCount () ; 
 int /*<<< orphan*/  NXGetTime (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NX_SINCE_BOOT ; 
 int /*<<< orphan*/  NX_TICKS ; 
 int /*<<< orphan*/  times (struct tms*) ; 

ulonglong my_timer_ticks(void)
{
#if defined(HAVE_SYS_TIMES_H) && defined(HAVE_TIMES)
  {
    struct tms times_buf;
    return (ulonglong) times(&times_buf);
  }
#elif defined(__NETWARE__)
  {
    NXTime_t tm;
    NXGetTime(NX_SINCE_BOOT, NX_TICKS, &tm);
    return (ulonglong) tm;
  }
#elif defined(_WIN32)
  return (ulonglong) GetTickCount();
#else
  return 0;
#endif
}