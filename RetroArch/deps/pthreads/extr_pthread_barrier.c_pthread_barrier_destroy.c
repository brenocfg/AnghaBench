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
typedef  TYPE_1__* pthread_barrier_t ;
struct TYPE_4__ {int /*<<< orphan*/  pshared; int /*<<< orphan*/ * semBarrierBreeched; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ PTE_OBJECT_INVALID ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int sem_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sem_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int pthread_barrier_destroy (pthread_barrier_t * barrier)
{
   int result = 0;
   pthread_barrier_t b;

   if (barrier == NULL || *barrier == (pthread_barrier_t) PTE_OBJECT_INVALID)
      return EINVAL;

   b = *barrier;
   *barrier = NULL;

   if (0 == (result = sem_destroy (&(b->semBarrierBreeched[0]))))
   {
      if (0 == (result = sem_destroy (&(b->semBarrierBreeched[1]))))
      {
         (void) free (b);
         return 0;
      }
      (void) sem_init (&(b->semBarrierBreeched[0]), b->pshared, 0);
   }

   *barrier = b;
   return (result);
}