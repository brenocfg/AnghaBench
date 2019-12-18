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
typedef  TYPE_1__* pthread_t ;
struct TYPE_4__ {int /*<<< orphan*/ * prevReuse; } ;
typedef  TYPE_1__ pte_thread_t ;

/* Variables and functions */
 void* PTE_THREAD_REUSE_EMPTY ; 
 int /*<<< orphan*/  pte_osMutexLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_osMutexUnlock (int /*<<< orphan*/ ) ; 
 void* pte_threadReuseBottom ; 
 void* pte_threadReuseTop ; 
 int /*<<< orphan*/  pte_thread_reuse_lock ; 

pthread_t
pte_threadReusePop (void)
{
   pthread_t t = NULL;

   pte_osMutexLock (pte_thread_reuse_lock);

   if (PTE_THREAD_REUSE_EMPTY != pte_threadReuseTop)
   {
      pte_thread_t * tp;

      tp = pte_threadReuseTop;

      pte_threadReuseTop = tp->prevReuse;

      if (PTE_THREAD_REUSE_EMPTY == pte_threadReuseTop)
         pte_threadReuseBottom = PTE_THREAD_REUSE_EMPTY;

      tp->prevReuse = NULL;

      t = tp;
   }

   pte_osMutexUnlock(pte_thread_reuse_lock);

   return t;

}