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
struct timespec {int dummy; } ;
typedef  TYPE_1__* pthread_rwlock_t ;
struct TYPE_5__ {scalar_t__ nMagic; scalar_t__ nExclusiveAccessCount; int /*<<< orphan*/  nSharedAccessCount; int /*<<< orphan*/  mtxSharedAccessCompleted; int /*<<< orphan*/  cndSharedAccessCompleted; int /*<<< orphan*/  nCompletedSharedAccessCount; int /*<<< orphan*/  mtxExclusiveAccess; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 scalar_t__ PTE_RWLOCK_MAGIC ; 
 TYPE_1__* PTHREAD_RWLOCK_INITIALIZER ; 
 int /*<<< orphan*/  pte_rwlock_cancelwrwait ; 
 int pte_rwlock_check_need_init (TYPE_1__**) ; 
 int /*<<< orphan*/  pthread_cleanup_pop (int) ; 
 int /*<<< orphan*/  pthread_cleanup_push (int /*<<< orphan*/ ,void*) ; 
 int pthread_cond_timedwait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timespec const*) ; 
 int pthread_mutex_timedlock (int /*<<< orphan*/ *,struct timespec const*) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

int pthread_rwlock_timedwrlock (pthread_rwlock_t * rwlock,
                            const struct timespec *abstime)
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
      {
         return result;
      }
   }

   rwl = *rwlock;

   if (rwl->nMagic != PTE_RWLOCK_MAGIC)
   {
      return EINVAL;
   }

   if ((result =
            pthread_mutex_timedlock (&(rwl->mtxExclusiveAccess), abstime)) != 0)
   {
      return result;
   }

   if ((result =
            pthread_mutex_timedlock (&(rwl->mtxSharedAccessCompleted),
               abstime)) != 0)
   {
      (void) pthread_mutex_unlock (&(rwl->mtxExclusiveAccess));
      return result;
   }

   if (rwl->nExclusiveAccessCount == 0)
   {
      if (rwl->nCompletedSharedAccessCount > 0)
      {
         rwl->nSharedAccessCount -= rwl->nCompletedSharedAccessCount;
         rwl->nCompletedSharedAccessCount = 0;
      }

      if (rwl->nSharedAccessCount > 0)
      {
         rwl->nCompletedSharedAccessCount = -rwl->nSharedAccessCount;

         /*
          * This routine may be a cancelation point
          * according to POSIX 1003.1j section 18.1.2.
          */
         pthread_cleanup_push (pte_rwlock_cancelwrwait, (void *) rwl);

         do
         {
            result =
               pthread_cond_timedwait (&(rwl->cndSharedAccessCompleted),
                     &(rwl->mtxSharedAccessCompleted),
                     abstime);
         }
         while (result == 0 && rwl->nCompletedSharedAccessCount < 0);

         pthread_cleanup_pop ((result != 0) ? 1 : 0);

         if (result == 0)
         {
            rwl->nSharedAccessCount = 0;
         }
      }
   }

   if (result == 0)
      rwl->nExclusiveAccessCount++;

   return result;
}