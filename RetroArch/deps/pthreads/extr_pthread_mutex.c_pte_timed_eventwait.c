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
struct timespec {int dummy; } ;
typedef  int /*<<< orphan*/  pte_osSemaphoreHandle ;
typedef  scalar_t__ pte_osResult ;

/* Variables and functions */
 int ETIMEDOUT ; 
 scalar_t__ PTE_OS_TIMEOUT ; 
 scalar_t__ pte_osSemaphorePend (int /*<<< orphan*/ ,unsigned int*) ; 
 unsigned int pte_relmillisecs (struct timespec const*) ; 

__attribute__((used)) static int pte_timed_eventwait (pte_osSemaphoreHandle event, const struct timespec *abstime)
/*
 * ------------------------------------------------------
 * DESCRIPTION
 *      This function waits on an event until signaled or until
 *      abstime passes.
 *      If abstime has passed when this routine is called then
 *      it returns a result to indicate this.
 *
 *      If 'abstime' is a NULL pointer then this function will
 *      block until it can successfully decrease the value or
 *      until interrupted by a signal.
 *
 *      This routine is not a cancelation point.
 *
 * RESULTS
 *              0               successfully signaled,
 *              ETIMEDOUT       abstime passed
 *              EINVAL          'event' is not a valid event,
 *
 * ------------------------------------------------------
 */
{
   unsigned int milliseconds;
   pte_osResult status;
   int retval;

   if (abstime == NULL)
      status = pte_osSemaphorePend(event, NULL);
   else
   {
      /*
       * Calculate timeout as milliseconds from current system time.
       */
      milliseconds = pte_relmillisecs (abstime);

      status = pte_osSemaphorePend(event, &milliseconds);
   }


   if (status == PTE_OS_TIMEOUT)
   {
      retval = ETIMEDOUT;
   }
   else
   {
      retval = 0;
   }

   return retval;

}