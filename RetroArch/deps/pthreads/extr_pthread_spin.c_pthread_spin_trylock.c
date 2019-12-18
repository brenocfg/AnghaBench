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
typedef  TYPE_2__* pthread_spinlock_t ;
struct TYPE_6__ {int /*<<< orphan*/  mutex; } ;
struct TYPE_7__ {TYPE_1__ u; int /*<<< orphan*/  interlock; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 scalar_t__ PTE_ATOMIC_COMPARE_EXCHANGE (int /*<<< orphan*/ *,int,int) ; 
#define  PTE_SPIN_LOCKED 130 
#define  PTE_SPIN_UNLOCKED 129 
#define  PTE_SPIN_USE_MUTEX 128 
 TYPE_2__* PTHREAD_SPINLOCK_INITIALIZER ; 
 int pte_spinlock_check_need_init (TYPE_2__**) ; 
 int pthread_mutex_trylock (int /*<<< orphan*/ *) ; 

int pthread_spin_trylock (pthread_spinlock_t * lock)
{
   register pthread_spinlock_t s;

   if (NULL == lock || NULL == *lock)
      return (EINVAL);

   if (*lock == PTHREAD_SPINLOCK_INITIALIZER)
   {
      int result;

      if ((result = pte_spinlock_check_need_init (lock)) != 0)
         return (result);
   }

   s = *lock;

   switch ((long)
         PTE_ATOMIC_COMPARE_EXCHANGE (&(s->interlock),
            PTE_SPIN_LOCKED,
            PTE_SPIN_UNLOCKED))
   {
      case PTE_SPIN_UNLOCKED:
         return 0;
      case PTE_SPIN_LOCKED:
         return EBUSY;
      case PTE_SPIN_USE_MUTEX:
         return pthread_mutex_trylock (&(s->u.mutex));
   }

   return EINVAL;
}