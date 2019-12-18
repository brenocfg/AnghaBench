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
struct timeval {int tv_usec; int /*<<< orphan*/  tv_sec; int /*<<< orphan*/  member_0; } ;
struct timespec {int tv_nsec; int /*<<< orphan*/  tv_sec; } ;
typedef  int clockid_t ;
typedef  int /*<<< orphan*/  OSTime ;

/* Variables and functions */
#define  CLOCK_REALTIME 128 
 int /*<<< orphan*/  EFAULT ; 
 int /*<<< orphan*/  EINVAL ; 
 int _gettimeofday_r (int /*<<< orphan*/ *,struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errno ; 

int clock_gettime(clockid_t clk_id, struct timespec* tp)
{
   struct timeval ptimeval = { 0 };
   int ret = 0;
   OSTime cosTime;

   if (tp == NULL) {
      errno = EFAULT;
      return -1;
   }

   switch (clk_id) {
      case CLOCK_REALTIME:
         /* Just wrap gettimeofday. Cheating, I know. */
         ret = _gettimeofday_r(NULL, &ptimeval, NULL);
         if (ret) return -1;

         tp->tv_sec = ptimeval.tv_sec;
         tp->tv_nsec = ptimeval.tv_usec * 1000;
      break;
      default:
         errno = EINVAL;
         return -1;
   }
   return 0;
}