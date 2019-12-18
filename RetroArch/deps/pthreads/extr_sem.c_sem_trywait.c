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
struct TYPE_3__ {scalar_t__ value; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EAGAIN ; 
 void* EINVAL ; 
 int errno ; 
 int pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

int sem_trywait (sem_t * sem)
   /*
    * ------------------------------------------------------
    * DOCPUBLIC
    *      This function tries to wait on a semaphore.
    *
    * PARAMETERS
    *      sem
    *              pointer to an instance of sem_t
    *
    * DESCRIPTION
    *      This function tries to wait on a semaphore. If the
    *      semaphore value is greater than zero, it decreases
    *      its value by one. If the semaphore value is zero, then
    *      this function returns immediately with the error EAGAIN
    *
    * RESULTS
    *              0               successfully decreased semaphore,
    *              -1              failed, error in errno
    * ERRNO
    *              EAGAIN          the semaphore was already locked,
    *              EINVAL          'sem' is not a valid semaphore,
    *              ENOTSUP         sem_trywait is not supported,
    *              EINTR           the function was interrupted by a signal,
    *              EDEADLK         a deadlock condition was detected.
    *
    * ------------------------------------------------------
    */
{
   int result = 0;
   sem_t s = *sem;

   if (s == NULL)
      result = EINVAL;
   else if ((result = pthread_mutex_lock (&s->lock)) == 0)
   {
      /* See sem_destroy.c
      */
      if (*sem == NULL)
      {
         (void) pthread_mutex_unlock (&s->lock);
         errno = EINVAL;
         return -1;
      }

      if (s->value > 0)
         s->value--;
      else
         result = EAGAIN;

      (void) pthread_mutex_unlock (&s->lock);
   }

   if (result != 0)
   {
      errno = result;
      return -1;
   }

   return 0;
}