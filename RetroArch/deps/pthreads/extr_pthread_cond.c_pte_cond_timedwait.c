#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct timespec {int dummy; } ;
typedef  int /*<<< orphan*/  pthread_mutex_t ;
typedef  TYPE_1__* pthread_cond_t ;
struct TYPE_7__ {int* resultPtr; TYPE_1__* cv; int /*<<< orphan*/ * mutexPtr; } ;
typedef  TYPE_2__ pte_cond_wait_cleanup_args_t ;
struct TYPE_6__ {int /*<<< orphan*/  semBlockQueue; int /*<<< orphan*/  semBlockLock; int /*<<< orphan*/  nWaitersBlocked; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 TYPE_1__* PTHREAD_COND_INITIALIZER ; 
 int errno ; 
 int pte_cond_check_need_init (TYPE_1__**) ; 
 int /*<<< orphan*/  pte_cond_wait_cleanup ; 
 int /*<<< orphan*/  pthread_cleanup_pop (int) ; 
 int /*<<< orphan*/  pthread_cleanup_push (int /*<<< orphan*/ ,void*) ; 
 int pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ sem_post (int /*<<< orphan*/ *) ; 
 scalar_t__ sem_timedwait (int /*<<< orphan*/ *,struct timespec const*) ; 
 scalar_t__ sem_wait (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pte_cond_timedwait (pthread_cond_t * cond,
      pthread_mutex_t * mutex, const struct timespec *abstime)
{
   int result = 0;
   pthread_cond_t cv;
   pte_cond_wait_cleanup_args_t cleanup_args;

   if (cond == NULL || *cond == NULL)
      return EINVAL;

   /*
    * We do a quick check to see if we need to do more work
    * to initialise a static condition variable. We check
    * again inside the guarded section of pte_cond_check_need_init()
    * to avoid race conditions.
    */
   if (*cond == PTHREAD_COND_INITIALIZER)
      result = pte_cond_check_need_init (cond);

   if (result != 0 && result != EBUSY)
      return result;

   cv = *cond;

   /* Thread can be cancelled in sem_wait() but this is OK */
   if (sem_wait (&(cv->semBlockLock)) != 0)
      return errno;

   ++(cv->nWaitersBlocked);

   if (sem_post (&(cv->semBlockLock)) != 0)
      return errno;

   /*
    * Setup this waiter cleanup handler
    */
   cleanup_args.mutexPtr = mutex;
   cleanup_args.cv = cv;
   cleanup_args.resultPtr = &result;

   pthread_cleanup_push (pte_cond_wait_cleanup, (void *) &cleanup_args);

   /*
    * Now we can release 'mutex' and...
    */
   if ((result = pthread_mutex_unlock (mutex)) == 0)
   {
      /*
       * ...wait to be awakened by
       *              pthread_cond_signal, or
       *              pthread_cond_broadcast, or
       *              timeout, or
       *              thread cancellation
       *
       * Note:
       *
       *      sem_timedwait is a cancellation point,
       *      hence providing the mechanism for making
       *      pthread_cond_wait a cancellation point.
       *      We use the cleanup mechanism to ensure we
       *      re-lock the mutex and adjust (to)unblock(ed) waiters
       *      counts if we are cancelled, timed out or signalled.
       */
      if (sem_timedwait (&(cv->semBlockQueue), abstime) != 0)
         result = errno;
   }


   /*
    * Always cleanup
    */
   pthread_cleanup_pop (1);

   /*
    * "result" can be modified by the cleanup handler.
    */
   return result;
}