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
struct timespec {scalar_t__ tv_nsec; scalar_t__ tv_sec; } ;
struct timeb {scalar_t__ millitm; scalar_t__ time; } ;
typedef  long long const int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  _ftime (struct timeb*) ; 

unsigned int pte_relmillisecs (const struct timespec * abstime)
{
   const long long NANOSEC_PER_MILLISEC = 1000000;
   const long long MILLISEC_PER_SEC = 1000;
   unsigned int milliseconds;
   long  tmpCurrMilliseconds;
   struct timeb currSysTime;

   /*
    * Calculate timeout as milliseconds from current system time.
    */

   /*
    * subtract current system time from abstime in a way that checks
    * that abstime is never in the past, or is never equivalent to the
    * defined INFINITE value (0xFFFFFFFF).
    *
    * Assume all integers are unsigned, i.e. cannot test if less than 0.
    */
   long long tmpAbsMilliseconds =  (int64_t)abstime->tv_sec * MILLISEC_PER_SEC;
   tmpAbsMilliseconds += ((int64_t)abstime->tv_nsec + (NANOSEC_PER_MILLISEC/2)) / NANOSEC_PER_MILLISEC;

   /* get current system time */

   _ftime(&currSysTime);

   tmpCurrMilliseconds = (int64_t) currSysTime.time * MILLISEC_PER_SEC;
   tmpCurrMilliseconds += (int64_t) currSysTime.millitm;

   if (tmpAbsMilliseconds > tmpCurrMilliseconds)
   {
      milliseconds = (unsigned int) (tmpAbsMilliseconds - tmpCurrMilliseconds);
      /* Timeouts must be finite */
      if (milliseconds == 0xFFFFFFFF)
         milliseconds--;
   }
   /* The abstime given is in the past */
   else
      milliseconds = 0;

   return milliseconds;
}