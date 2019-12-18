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
typedef  int /*<<< orphan*/  pthread_mutex_t ;
typedef  int /*<<< orphan*/  pthread_cond_t ;

/* Variables and functions */
 int pte_cond_timedwait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int pthread_cond_wait (pthread_cond_t * cond, pthread_mutex_t * mutex)
   /*
    * ------------------------------------------------------
    * DOCPUBLIC
    *      This function waits on a condition variable until
    *      awakened by a signal or broadcast.
    *
    *      Caller MUST be holding the mutex lock; the
    *      lock is released and the caller is blocked waiting
    *      on 'cond'. When 'cond' is signaled, the mutex
    *      is re-acquired before returning to the caller.
    *
    * PARAMETERS
    *      cond
    *              pointer to an instance of pthread_cond_t
    *
    *      mutex
    *              pointer to an instance of pthread_mutex_t
    *
    *
    * DESCRIPTION
    *      This function waits on a condition variable until
    *      awakened by a signal or broadcast.
    *
    *      NOTES:
    *
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
    * Upon successful completion, the 'mutex' has been locked and
    * is owned by the calling thread.
    *
    *
    * RESULTS
    *              0               caught condition; mutex released,
    *              EINVAL          'cond' or 'mutex' is invalid,
    *              EINVAL          different mutexes for concurrent waits,
    *              EINVAL          mutex is not held by the calling thread,
    *
    * ------------------------------------------------------
    */
{
   /*
    * The NULL abstime arg means INFINITE waiting.
    */
   return (pte_cond_timedwait (cond, mutex, NULL));

}