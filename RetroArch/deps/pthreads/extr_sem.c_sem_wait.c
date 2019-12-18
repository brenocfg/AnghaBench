#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* sem_t ;
struct TYPE_3__ {int value; int /*<<< orphan*/  sem; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 void* EINVAL ; 
 int errno ; 
 int pte_cancellable_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pte_sem_wait_cleanup ; 
 int /*<<< orphan*/  pthread_cleanup_pop (int) ; 
 int /*<<< orphan*/  pthread_cleanup_push (int /*<<< orphan*/ ,void*) ; 
 int pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_testcancel () ; 

int sem_wait (sem_t * sem)
   /*
    * ------------------------------------------------------
    * DOCPUBLIC
    *      This function  waits on a semaphore.
    *
    * PARAMETERS
    *      sem
    *              pointer to an instance of sem_t
    *
    * DESCRIPTION
    *      This function waits on a semaphore. If the
    *      semaphore value is greater than zero, it decreases
    *      its value by one. If the semaphore value is zero, then
    *      the calling thread (or process) is blocked until it can
    *      successfully decrease the value or until interrupted by
    *      a signal.
    *
    * RESULTS
    *              0               successfully decreased semaphore,
    *              -1              failed, error in errno
    * ERRNO
    *              EINVAL          'sem' is not a valid semaphore,
    *              ENOSYS          semaphores are not supported,
    *              EINTR           the function was interrupted by a signal,
    *              EDEADLK         a deadlock condition was detected.
    *
    * ------------------------------------------------------
    */
{
   int result = 0;
   sem_t s = *sem;

   pthread_testcancel();

   if (s == NULL)
   {
      result = EINVAL;
   }
   else
   {
      if ((result = pthread_mutex_lock (&s->lock)) == 0)
      {
         int v;

         /* See sem_destroy.c
         */
         if (*sem == NULL)
         {
            (void) pthread_mutex_unlock (&s->lock);
            errno = EINVAL;
            return -1;
         }

         v = --s->value;
         (void) pthread_mutex_unlock (&s->lock);

         if (v < 0)
         {
            /* Must wait */
            pthread_cleanup_push(pte_sem_wait_cleanup, (void *) s);
            result = pte_cancellable_wait(s->sem,NULL);
            /* Cleanup if we're canceled or on any other error */
            pthread_cleanup_pop(result);

            // Wait was cancelled, indicate that we're no longer waiting on this semaphore.
            /*
               if (result == PTE_OS_INTERRUPTED)
               {
               result = EINTR;
               ++s->value;
               }
               */
         }
      }

   }

   if (result != 0)
   {
      errno = result;
      return -1;
   }

   return 0;

}