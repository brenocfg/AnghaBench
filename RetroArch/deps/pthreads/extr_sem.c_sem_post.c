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
typedef  scalar_t__ pte_osResult ;
struct TYPE_3__ {scalar_t__ value; int /*<<< orphan*/  lock; int /*<<< orphan*/  sem; } ;

/* Variables and functions */
 int EINVAL ; 
 int ERANGE ; 
 scalar_t__ PTE_OS_OK ; 
 scalar_t__ SEM_VALUE_MAX ; 
 int errno ; 
 scalar_t__ pte_osSemaphorePost (int /*<<< orphan*/ ,int) ; 
 int pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

int
sem_post (sem_t * sem)
/*
 * ------------------------------------------------------
 * DOCPUBLIC
 *      This function posts a wakeup to a semaphore.
 *
 * PARAMETERS
 *      sem
 *              pointer to an instance of sem_t
 *
 * DESCRIPTION
 *      This function posts a wakeup to a semaphore. If there
 *      are waiting threads (or processes), one is awakened;
 *      otherwise, the semaphore value is incremented by one.
 *
 * RESULTS
 *              0               successfully posted semaphore,
 *              -1              failed, error in errno
 * ERRNO
 *              EINVAL          'sem' is not a valid semaphore,
 *              ENOSYS          semaphores are not supported,
 *              ERANGE          semaphore count is too big
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
         result = EINVAL;
         return -1;
      }

      if (s->value < SEM_VALUE_MAX)
      {
         pte_osResult osResult = pte_osSemaphorePost(s->sem, 1);

         if (++s->value <= 0
               && (osResult != PTE_OS_OK))
         {
            s->value--;
            result = EINVAL;
         }

      }
      else
         result = ERANGE;

      (void) pthread_mutex_unlock (&s->lock);
   }

   if (result != 0)
   {
      errno = result;
      return -1;
   }

   return 0;
}