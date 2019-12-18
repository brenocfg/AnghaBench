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
typedef  int /*<<< orphan*/  pthread_cond_t ;

/* Variables and functions */
 int pte_cond_unblock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int pthread_cond_signal (pthread_cond_t * cond)
   /*
    * ------------------------------------------------------
    * DOCPUBLIC
    *      This function signals a condition variable, waking
    *      one waiting thread.
    *      If SCHED_FIFO or SCHED_RR policy threads are waiting
    *      the highest priority waiter is awakened; otherwise,
    *      an unspecified waiter is awakened.
    *
    * PARAMETERS
    *      cond
    *              pointer to an instance of pthread_cond_t
    *
    *
    * DESCRIPTION
    *      This function signals a condition variable, waking
    *      one waiting thread.
    *      If SCHED_FIFO or SCHED_RR policy threads are waiting
    *      the highest priority waiter is awakened; otherwise,
    *      an unspecified waiter is awakened.
    *
    *      NOTES:
    *
    *      1)      Use when any waiter can respond and only one need
    *              respond (all waiters being equal).
    *
    * RESULTS
    *              0               successfully signaled condition,
    *              EINVAL          'cond' is invalid,
    *
    * ------------------------------------------------------
    */
{
   /*
    * The '0'(FALSE) unblockAll arg means unblock ONE waiter.
    */
   return (pte_cond_unblock (cond, 0));

}