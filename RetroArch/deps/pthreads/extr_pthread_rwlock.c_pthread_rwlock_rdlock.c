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
typedef  TYPE_1__* pthread_rwlock_t ;
struct TYPE_5__ {scalar_t__ nMagic; scalar_t__ nSharedAccessCount; scalar_t__ nCompletedSharedAccessCount; int /*<<< orphan*/  mtxExclusiveAccess; int /*<<< orphan*/  mtxSharedAccessCompleted; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 scalar_t__ INT_MAX ; 
 scalar_t__ PTE_RWLOCK_MAGIC ; 
 TYPE_1__* PTHREAD_RWLOCK_INITIALIZER ; 
 int pte_rwlock_check_need_init (TYPE_1__**) ; 
 int pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

int pthread_rwlock_rdlock (pthread_rwlock_t * rwlock)
{
   int result;
   pthread_rwlock_t rwl;

   if (rwlock == NULL || *rwlock == NULL)
      return EINVAL;

   /*
    * We do a quick check to see if we need to do more work
    * to initialise a static rwlock. We check
    * again inside the guarded section of pte_rwlock_check_need_init()
    * to avoid race conditions.
    */
   if (*rwlock == PTHREAD_RWLOCK_INITIALIZER)
   {
      result = pte_rwlock_check_need_init (rwlock);

      if (result != 0 && result != EBUSY)
         return result;
   }

   rwl = *rwlock;

   if (rwl->nMagic != PTE_RWLOCK_MAGIC)
      return EINVAL;

   if ((result = pthread_mutex_lock (&(rwl->mtxExclusiveAccess))) != 0)
      return result;

   if (++rwl->nSharedAccessCount == INT_MAX)
   {
      if ((result =
               pthread_mutex_lock (&(rwl->mtxSharedAccessCompleted))) != 0)
      {
         (void) pthread_mutex_unlock (&(rwl->mtxExclusiveAccess));
         return result;
      }

      rwl->nSharedAccessCount -= rwl->nCompletedSharedAccessCount;
      rwl->nCompletedSharedAccessCount = 0;

      if ((result =
               pthread_mutex_unlock (&(rwl->mtxSharedAccessCompleted))) != 0)
      {
         (void) pthread_mutex_unlock (&(rwl->mtxExclusiveAccess));
         return result;
      }
   }

   return (pthread_mutex_unlock (&(rwl->mtxExclusiveAccess)));
}