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
struct TYPE_3__ {int value; int /*<<< orphan*/  lock; int /*<<< orphan*/  sem; } ;

/* Variables and functions */
 int EINVAL ; 
 int ERANGE ; 
 int SEM_VALUE_MAX ; 
 int errno ; 
 int /*<<< orphan*/  pte_osSemaphorePost (int /*<<< orphan*/ ,long) ; 
 int pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

int
sem_post_multiple (sem_t * sem, int count)
/*
 * ------------------------------------------------------
 * DOCPUBLIC
 *      This function posts multiple wakeups to a semaphore.
 *
 * PARAMETERS
 *      sem
 *              pointer to an instance of sem_t
 *
 *      count
 *              counter, must be greater than zero.
 *
 * DESCRIPTION
 *      This function posts multiple wakeups to a semaphore. If there
 *      are waiting threads (or processes), n <= count are awakened;
 *      the semaphore value is incremented by count - n.
 *
 * RESULTS
 *              0               successfully posted semaphore,
 *              -1              failed, error in errno
 * ERRNO
 *              EINVAL          'sem' is not a valid semaphore
 *                              or count is less than or equal to zero.
 *              ERANGE          semaphore count is too big
 *
 * ------------------------------------------------------
 */
{
   int result = 0;
   long waiters;
   sem_t s = *sem;

   if (s == NULL || count <= 0)
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

      if (s->value <= (SEM_VALUE_MAX - count))
      {
         waiters = -s->value;
         s->value += count;
         if (waiters > 0)
         {

            pte_osSemaphorePost(s->sem, (waiters<=count)?waiters:count);
            result = 0;
         }
         /*
            else
            {
            s->value -= count;
            result = EINVAL;
            }
            */
      }
      else
      {
         result = ERANGE;
      }

      (void) pthread_mutex_unlock (&s->lock);
   }

   if (result != 0)
   {
      errno = result;
      return -1;
   }

   return 0;
}