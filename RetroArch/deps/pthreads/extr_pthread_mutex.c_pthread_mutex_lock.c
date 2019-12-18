#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* pthread_t ;
typedef  TYPE_1__* pthread_mutex_t ;
struct TYPE_5__ {scalar_t__ kind; int recursive_count; void* ownerThread; int /*<<< orphan*/  handle; int /*<<< orphan*/  lock_idx; } ;

/* Variables and functions */
 int EDEADLK ; 
 int EINVAL ; 
 scalar_t__ PTE_ATOMIC_COMPARE_EXCHANGE (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ PTE_ATOMIC_EXCHANGE (int /*<<< orphan*/ *,int) ; 
 scalar_t__ PTE_OS_OK ; 
 TYPE_1__* PTHREAD_ERRORCHECK_MUTEX_INITIALIZER ; 
 scalar_t__ PTHREAD_MUTEX_NORMAL ; 
 scalar_t__ PTHREAD_MUTEX_RECURSIVE ; 
 int pte_mutex_check_need_init (TYPE_1__**) ; 
 scalar_t__ pte_osSemaphorePend (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_equal (void*,void*) ; 
 void* pthread_self () ; 

int pthread_mutex_lock (pthread_mutex_t * mutex)
{
   int result = 0;
   pthread_mutex_t mx;

   /*
    * Let the system deal with invalid pointers.
    */
   if (*mutex == NULL)
      return EINVAL;

   /*
    * We do a quick check to see if we need to do more work
    * to initialise a static mutex. We check
    * again inside the guarded section of pte_mutex_check_need_init()
    * to avoid race conditions.
    */
   if (*mutex >= PTHREAD_ERRORCHECK_MUTEX_INITIALIZER)
   {
      if ((result = pte_mutex_check_need_init (mutex)) != 0)
         return (result);
   }

   mx = *mutex;

   if (mx->kind == PTHREAD_MUTEX_NORMAL)
   {
      if (PTE_ATOMIC_EXCHANGE(
               &mx->lock_idx,
               1) != 0)
      {
         while (PTE_ATOMIC_EXCHANGE(&mx->lock_idx,-1) != 0)
         {
            if (pte_osSemaphorePend(mx->handle,NULL) != PTE_OS_OK)
            {
               result = EINVAL;
               break;
            }
         }
      }
   }
   else
   {
      pthread_t self = pthread_self();

      if (PTE_ATOMIC_COMPARE_EXCHANGE(&mx->lock_idx,1,0) == 0)
      {
         mx->recursive_count = 1;
         mx->ownerThread = self;
      }
      else
      {
         if (pthread_equal (mx->ownerThread, self))
         {
            if (mx->kind == PTHREAD_MUTEX_RECURSIVE)
               mx->recursive_count++;
            else
               result = EDEADLK;
         }
         else
         {
            while (PTE_ATOMIC_EXCHANGE(&mx->lock_idx,-1) != 0)
            {
               if (pte_osSemaphorePend(mx->handle,NULL) != PTE_OS_OK)
               {
                  result = EINVAL;
                  break;
               }
            }

            if (0 == result)
            {
               mx->recursive_count = 1;
               mx->ownerThread = self;
            }
         }
      }

   }

   return (result);
}