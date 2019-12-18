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
struct TYPE_5__ {struct TYPE_5__* prevReuse; } ;
typedef  TYPE_1__ pte_thread_t ;

/* Variables and functions */
 scalar_t__ PTE_FALSE ; 
 TYPE_1__* PTE_THREAD_REUSE_EMPTY ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/ * pte_cleanupKey ; 
 int /*<<< orphan*/  pte_osMutexLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_osMutexUnlock (int /*<<< orphan*/ ) ; 
 scalar_t__ pte_processInitialized ; 
 int /*<<< orphan*/ * pte_selfThreadKey ; 
 TYPE_1__* pte_threadReuseTop ; 
 int /*<<< orphan*/  pte_thread_reuse_lock ; 
 int /*<<< orphan*/  pthread_key_delete (int /*<<< orphan*/ *) ; 

void pthread_terminate(void)
{
   pte_thread_t * tp, * tpNext;

   if (!pte_processInitialized)
      return;

   if (pte_selfThreadKey != NULL)
   {
      /*
       * Release pte_selfThreadKey
       */
      pthread_key_delete (pte_selfThreadKey);

      pte_selfThreadKey = NULL;
   }

   if (pte_cleanupKey != NULL)
   {
      /*
       * Release pte_cleanupKey
       */
      pthread_key_delete (pte_cleanupKey);

      pte_cleanupKey = NULL;
   }

   pte_osMutexLock (pte_thread_reuse_lock);


   tp = pte_threadReuseTop;
   while (tp != PTE_THREAD_REUSE_EMPTY)
   {
      tpNext = tp->prevReuse;
      free (tp);
      tp = tpNext;
   }

   pte_osMutexUnlock(pte_thread_reuse_lock);

   pte_processInitialized = PTE_FALSE;
}