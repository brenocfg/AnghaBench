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
 int /*<<< orphan*/  PTE_TRUE ; 
 int pte_cond_unblock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
pthread_cond_broadcast (pthread_cond_t * cond)
   /*
    * ------------------------------------------------------
    * DOCPUBLIC
    *      This function broadcasts the condition variable,
    *      waking all current waiters.
    *
    * PARAMETERS
    *      cond
    *              pointer to an instance of pthread_cond_t
    *
    *
    * DESCRIPTION
    *      This function signals a condition variable, waking
    *      all waiting threads.
    *
    *      NOTES:
    *
    *      1)      Use when more than one waiter may respond to
    *              predicate change or if any waiting thread may
    *              not be able to respond
    *
    * RESULTS
    *              0               successfully signalled condition to all
    *                              waiting threads,
    *              EINVAL          'cond' is invalid
    *              ENOSPC          a required resource has been exhausted,
    *
    * ------------------------------------------------------
    */
{
   /*
    * The TRUE unblockAll arg means unblock ALL waiters.
    */
   return (pte_cond_unblock (cond, PTE_TRUE));
}