#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct timespec {long tv_sec; long tv_nsec; } ;
typedef  int /*<<< orphan*/ * pthread_t ;
struct TYPE_2__ {scalar_t__ cancelState; scalar_t__ state; int /*<<< orphan*/  cancelLock; int /*<<< orphan*/  threadId; } ;
typedef  TYPE_1__ pte_thread_t ;
typedef  scalar_t__ pte_osResult ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int ESRCH ; 
 int /*<<< orphan*/  PTE_EPS_CANCEL ; 
 scalar_t__ PTE_OS_INTERRUPTED ; 
 scalar_t__ PTE_OS_OK ; 
 scalar_t__ PTHREAD_CANCEL_DISABLE ; 
 scalar_t__ PTHREAD_CANCEL_ENABLE ; 
 scalar_t__ PThreadStateCanceling ; 
 scalar_t__ pte_osThreadCheckCancel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_osThreadSleep (unsigned int) ; 
 int /*<<< orphan*/  pte_throw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pthread_self () ; 
 int /*<<< orphan*/  pthread_testcancel () ; 

int pthread_delay_np (struct timespec *interval)
{
   unsigned int wait_time;
   unsigned int secs_in_millisecs;
   unsigned int millisecs;
   pthread_t self;
   pte_thread_t * sp;

   if (interval == NULL)
      return EINVAL;

   if (interval->tv_sec == 0L && interval->tv_nsec == 0L)
   {
      pthread_testcancel ();
      pte_osThreadSleep (1);
      pthread_testcancel ();
      return (0);
   }

   /* convert secs to millisecs */
   secs_in_millisecs = interval->tv_sec * 1000L;

   /* convert nanosecs to millisecs (rounding up) */
   millisecs = (interval->tv_nsec + 999999L) / 1000000L;

   wait_time = secs_in_millisecs + millisecs;

   if (NULL == (self = pthread_self ()))
      return ENOMEM;

   sp = (pte_thread_t *) self;

   if (sp->cancelState == PTHREAD_CANCEL_ENABLE)
   {
      pte_osResult cancelStatus;
      /*
       * Async cancelation won't catch us until wait_time is up.
       * Deferred cancelation will cancel us immediately.
       */
      cancelStatus = pte_osThreadCheckCancel(sp->threadId);

      if (cancelStatus == PTE_OS_INTERRUPTED)
      {
         /*
          * Canceling!
          */
         (void) pthread_mutex_lock (&sp->cancelLock);
         if (sp->state < PThreadStateCanceling)
         {
            sp->state = PThreadStateCanceling;
            sp->cancelState = PTHREAD_CANCEL_DISABLE;
            (void) pthread_mutex_unlock (&sp->cancelLock);

            pte_throw (PTE_EPS_CANCEL);
         }

         (void) pthread_mutex_unlock (&sp->cancelLock);
         return ESRCH;
      }
      else if (cancelStatus != PTE_OS_OK)
         return EINVAL;
   }
   else

      pte_osThreadSleep (wait_time);

   return (0);
}