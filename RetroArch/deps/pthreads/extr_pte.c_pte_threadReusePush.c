#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* pthread_t ;
struct TYPE_8__ {struct TYPE_8__* prevReuse; scalar_t__ x; } ;
typedef  TYPE_1__ pte_thread_t ;

/* Variables and functions */
 scalar_t__ PTE_THREAD_ID_REUSE_INCREMENT ; 
 TYPE_1__* PTE_THREAD_REUSE_EMPTY ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pte_osMutexLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_osMutexUnlock (int /*<<< orphan*/ ) ; 
 TYPE_1__* pte_threadReuseBottom ; 
 TYPE_1__* pte_threadReuseTop ; 
 int /*<<< orphan*/  pte_thread_reuse_lock ; 

void pte_threadReusePush (pthread_t thread)
{
   pte_thread_t * tp = (pte_thread_t *) thread;
   pthread_t t;

   pte_osMutexLock (pte_thread_reuse_lock);

   t = tp;
   memset(tp, 0, sizeof(pte_thread_t));

   /* Must restore the original POSIX handle that we just wiped. */
   tp = t;

   /* Bump the reuse counter now */
#ifdef PTE_THREAD_ID_REUSE_INCREMENT
   tp->x += PTE_THREAD_ID_REUSE_INCREMENT;
#else
   tp->x++;
#endif

   tp->prevReuse = PTE_THREAD_REUSE_EMPTY;

   if (PTE_THREAD_REUSE_EMPTY != pte_threadReuseBottom)
      pte_threadReuseBottom->prevReuse = tp;
   else
      pte_threadReuseTop = tp;

   pte_threadReuseBottom = tp;

   pte_osMutexUnlock(pte_thread_reuse_lock);
}