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
typedef  TYPE_1__* pthread_rwlock_t ;
struct TYPE_4__ {scalar_t__ nMagic; scalar_t__ nExclusiveAccessCount; scalar_t__ nCompletedSharedAccessCount; int /*<<< orphan*/  mtxExclusiveAccess; int /*<<< orphan*/  mtxSharedAccessCompleted; int /*<<< orphan*/  cndSharedAccessCompleted; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ PTE_RWLOCK_MAGIC ; 
 TYPE_1__* PTHREAD_RWLOCK_INITIALIZER ; 
 int pthread_cond_signal (int /*<<< orphan*/ *) ; 
 int pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

int pthread_rwlock_unlock (pthread_rwlock_t * rwlock)
{
   int result, result1;
   pthread_rwlock_t rwl;

   if (rwlock == NULL || *rwlock == NULL)
      return (EINVAL);

   if (*rwlock == PTHREAD_RWLOCK_INITIALIZER)
   {
      /*
       * Assume any race condition here is harmless.
       */
      return 0;
   }

   rwl = *rwlock;

   if (rwl->nMagic != PTE_RWLOCK_MAGIC)
   {
      return EINVAL;
   }

   if (rwl->nExclusiveAccessCount == 0)
   {
      if ((result =
               pthread_mutex_lock (&(rwl->mtxSharedAccessCompleted))) != 0)
      {
         return result;
      }

      if (++rwl->nCompletedSharedAccessCount == 0)
      {
         result = pthread_cond_signal (&(rwl->cndSharedAccessCompleted));
      }

      result1 = pthread_mutex_unlock (&(rwl->mtxSharedAccessCompleted));
   }
   else
   {
      rwl->nExclusiveAccessCount--;

      result = pthread_mutex_unlock (&(rwl->mtxSharedAccessCompleted));
      result1 = pthread_mutex_unlock (&(rwl->mtxExclusiveAccess));

   }

   return ((result != 0) ? result : result1);
}