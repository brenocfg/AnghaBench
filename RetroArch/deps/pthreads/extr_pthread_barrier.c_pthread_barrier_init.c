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
typedef  TYPE_1__* pthread_barrierattr_t ;
typedef  TYPE_2__* pthread_barrier_t ;
struct TYPE_7__ {unsigned int nCurrentBarrierHeight; unsigned int nInitialBarrierHeight; int /*<<< orphan*/ * semBarrierBreeched; int /*<<< orphan*/  pshared; scalar_t__ iStep; } ;
struct TYPE_6__ {int /*<<< orphan*/  pshared; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  PTHREAD_PROCESS_PRIVATE ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  sem_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ sem_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int pthread_barrier_init (pthread_barrier_t * barrier,
      const pthread_barrierattr_t * attr, unsigned int count)
{
   pthread_barrier_t b;

   if (barrier == NULL || count == 0)
      return EINVAL;

   if (NULL != (b = (pthread_barrier_t) calloc (1, sizeof (*b))))
   {
      b->pshared = (attr != NULL && *attr != NULL
            ? (*attr)->pshared : PTHREAD_PROCESS_PRIVATE);

      b->nCurrentBarrierHeight = b->nInitialBarrierHeight = count;
      b->iStep = 0;

      /*
       * Two semaphores are used in the same way as two stepping
       * stones might be used in crossing a stream. Once all
       * threads are safely on one stone, the other stone can
       * be moved ahead, and the threads can start moving to it.
       * If some threads decide to eat their lunch before moving
       * then the other threads have to wait.
       */
      if (0 == sem_init (&(b->semBarrierBreeched[0]), b->pshared, 0))
      {
         if (0 == sem_init (&(b->semBarrierBreeched[1]), b->pshared, 0))
         {
            *barrier = b;
            return 0;
         }
         (void) sem_destroy (&(b->semBarrierBreeched[0]));
      }
      (void) free (b);
   }

   return ENOMEM;
}