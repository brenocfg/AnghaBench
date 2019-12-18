#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* sem_t ;
typedef  scalar_t__ pte_osResult ;
struct TYPE_4__ {unsigned int value; int /*<<< orphan*/  lock; int /*<<< orphan*/  sem; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int ENOSPC ; 
 int EPERM ; 
 scalar_t__ PTE_OS_OK ; 
 scalar_t__ SEM_VALUE_MAX ; 
 scalar_t__ calloc (int,int) ; 
 int errno ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 scalar_t__ pte_osSemaphoreCreate (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
sem_init (sem_t * sem, int pshared, unsigned int value)
/*
 * ------------------------------------------------------
 * DOCPUBLIC
 *      This function initializes a semaphore. The
 *      initial value of the semaphore is 'value'
 *
 * PARAMETERS
 *      sem
 *              pointer to an instance of sem_t
 *
 *      pshared
 *              if zero, this semaphore may only be shared between
 *              threads in the same process.
 *              if nonzero, the semaphore can be shared between
 *              processes
 *
 *      value
 *              initial value of the semaphore counter
 *
 * DESCRIPTION
 *      This function initializes a semaphore. The
 *      initial value of the semaphore is set to 'value'.
 *
 * RESULTS
 *              0               successfully created semaphore,
 *              -1              failed, error in errno
 * ERRNO
 *              EINVAL          'sem' is not a valid semaphore, or
 *                              'value' >= SEM_VALUE_MAX
 *              ENOMEM          out of memory,
 *              ENOSPC          a required resource has been exhausted,
 *              ENOSYS          semaphores are not supported,
 *              EPERM           the process lacks appropriate privilege
 *
 * ------------------------------------------------------
 */
{
   int result = 0;
   sem_t s = NULL;

   if (pshared != 0)
   {
      /*
       * Creating a semaphore that can be shared between
       * processes
       */
      result = EPERM;
   }
   else if (value > (unsigned int)SEM_VALUE_MAX)
   {
      result = EINVAL;
   }
   else
   {
      s = (sem_t) calloc (1, sizeof (*s));

      if (NULL == s)
      {
         result = ENOMEM;
      }
      else
      {

         s->value = value;
         if (pthread_mutex_init(&s->lock, NULL) == 0)
         {

            pte_osResult osResult = pte_osSemaphoreCreate(0, &s->sem);



            if (osResult != PTE_OS_OK)
            {
               (void) pthread_mutex_destroy(&s->lock);
               result = ENOSPC;
            }

         }
         else
         {
            result = ENOSPC;
         }

         if (result != 0)
         {
            free(s);
         }
      }
   }

   if (result != 0)
   {
      errno = result;
      return -1;
   }

   *sem = s;

   return 0;
}