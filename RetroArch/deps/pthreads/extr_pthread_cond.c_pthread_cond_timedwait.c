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
typedef  int /*<<< orphan*/  pthread_mutex_t ;
typedef  int /*<<< orphan*/  pthread_cond_t ;

/* Variables and functions */
 int EINVAL ; 
 int pte_cond_timedwait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timespec const*) ; 

int
pthread_cond_timedwait (pthread_cond_t * cond,
      pthread_mutex_t * mutex,
      const struct timespec *abstime)
   /*
    * ------------------------------------------------------
    * DOCPUBLIC
    *      This function waits on a condition variable either until
    *      awakened by a signal or broadcast; or until the time
    *      specified by abstime passes.
    *
    * PARAMETERS
    *      cond
    *              pointer to an instance of pthread_cond_t
    *
    *      mutex
    *              pointer to an instance of pthread_mutex_t
    *
    *      abstime
    *              pointer to an instance of (const struct timespec)
    *
    *
    * DESCRIPTION
    *      This function waits on a condition variable either until
    *      awakened by a signal or broadcast; or until the time
    *      specified by abstime passes.
    *
    *      NOTES:
    *      1)      The function must be called with 'mutex' LOCKED
    *              by the calling thread, or undefined behaviour
    *              will result.
    *
    *      2)      This routine atomically releases 'mutex' and causes
    *              the calling thread to block on the condition variable.
    *              The blocked thread may be awakened by
    *                      pthread_cond_signal or
    *                      pthread_cond_broadcast.
    *
    *
    * RESULTS
    *              0               caught condition; mutex released,
    *              EINVAL          'cond', 'mutex', or abstime is invalid,
    *              EINVAL          different mutexes for concurrent waits,
    *              EINVAL          mutex is not held by the calling thread,
    *              ETIMEDOUT       abstime ellapsed before cond was signaled.
    *
    * ------------------------------------------------------
    */
{
   if (abstime == NULL)
   {
      return EINVAL;
   }

   return (pte_cond_timedwait (cond, mutex, abstime));
}