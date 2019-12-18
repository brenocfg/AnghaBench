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
typedef  TYPE_1__* pthread_mutex_t ;
struct TYPE_4__ {scalar_t__ kind; scalar_t__ recursive_count; int /*<<< orphan*/  handle; int /*<<< orphan*/  lock_idx; int /*<<< orphan*/ * ownerThread; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 int PTE_ATOMIC_EXCHANGE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ PTE_OS_OK ; 
 TYPE_1__* PTHREAD_ERRORCHECK_MUTEX_INITIALIZER ; 
 scalar_t__ PTHREAD_MUTEX_NORMAL ; 
 scalar_t__ PTHREAD_MUTEX_RECURSIVE ; 
 scalar_t__ pte_osSemaphorePost (int /*<<< orphan*/ ,int) ; 
 scalar_t__ pthread_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_self () ; 

int pthread_mutex_unlock (pthread_mutex_t * mutex)
{
   int result         = 0;
   pthread_mutex_t mx = *mutex;

   /*
    * Let the system deal with invalid pointers.
    */

   /*
    * If the thread calling us holds the mutex then there is no
    * race condition. If another thread holds the
    * lock then we shouldn't be in here.
    */
   if (mx < PTHREAD_ERRORCHECK_MUTEX_INITIALIZER)
   {
      if (mx->kind == PTHREAD_MUTEX_NORMAL)
      {
         int idx;

         idx = PTE_ATOMIC_EXCHANGE (&mx->lock_idx,0);
         if (idx != 0)
         {
            if (idx < 0)
            {
               /*
                * Someone may be waiting on that mutex.
                */
               if (pte_osSemaphorePost(mx->handle,1) != PTE_OS_OK)
                  result = EINVAL;
            }
         }
         else
         {
            /*
             * Was not locked (so can't be owned by us).
             */
            result = EPERM;
         }
      }
      else
      {
         if (pthread_equal (mx->ownerThread, pthread_self ()))
         {
            if (mx->kind != PTHREAD_MUTEX_RECURSIVE
                  || 0 == --mx->recursive_count)
            {
               mx->ownerThread = NULL;

               if (PTE_ATOMIC_EXCHANGE (&mx->lock_idx,0) < 0)
               {
                  if (pte_osSemaphorePost(mx->handle,1) != PTE_OS_OK)
                     result = EINVAL;
               }
            }
         }
         else
            result = EPERM;
      }
   }
   else
      result = EINVAL;

   return (result);
}