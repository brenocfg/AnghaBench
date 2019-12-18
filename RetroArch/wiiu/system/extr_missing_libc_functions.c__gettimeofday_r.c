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
typedef  int uint64_t ;
typedef  scalar_t__ uint32_t ;
typedef  int time_t ;
struct timeval {int tv_sec; scalar_t__ tv_usec; } ;
struct _reent {int dummy; } ;
typedef  int /*<<< orphan*/  OSTime ;

/* Variables and functions */
 int /*<<< orphan*/  EFAULT ; 
 int /*<<< orphan*/  OSGetTime () ; 
 int /*<<< orphan*/  errno ; 
 int ticks_to_sec (int /*<<< orphan*/ ) ; 
 scalar_t__ ticks_to_us (int /*<<< orphan*/ ) ; 

int _gettimeofday_r(struct _reent *ptr,
   struct timeval* ptimeval,
   void* ptimezone)
{
   OSTime cosTime;
   uint64_t cosSecs;
   uint32_t cosUSecs;
   time_t unixSecs;

   /* We need somewhere to put our output */
   if (ptimeval == NULL)
   {
      errno = EFAULT;
      return -1;
   }

   /* Get Cafe OS clock in seconds; epoch 2000-01-01 00:00 */
   cosTime = OSGetTime();
   cosSecs = ticks_to_sec(cosTime);

   /* Get extra milliseconds */
   cosUSecs = ticks_to_us(cosTime) - (cosSecs * 1000000);

   /* Convert to Unix time, epoch 1970-01-01 00:00.
      Constant value is seconds between 1970 and 2000.
      time_t is 32bit here, so the Wii U is vulnerable to the 2038 problem. */
   unixSecs = cosSecs + 946684800;

   ptimeval->tv_sec = unixSecs;
   ptimeval->tv_usec = cosUSecs;
   return 0;
}