#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ waiters; scalar_t__ wakens; int /*<<< orphan*/  cond; int /*<<< orphan*/  hot_potato; int /*<<< orphan*/  cs; int /*<<< orphan*/  event; } ;
typedef  TYPE_1__ scond_t ;

/* Variables and functions */
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_cond_signal (int /*<<< orphan*/ *) ; 

void scond_signal(scond_t *cond)
{
#ifdef USE_WIN32_THREADS

   /* Unfortunately, pthread_cond_signal does not require that the
    * lock be held in advance */
   /* To avoid stomping on the condvar from other threads, we need
    * to control access to it with this */
   EnterCriticalSection(&cond->cs);

   /* remember: we currently have mutex */
   if (cond->waiters == 0)
   {
      LeaveCriticalSection(&cond->cs);
      return;
   }

   /* wake up the next thing in the queue */
   if (cond->wakens == 0)
      SetEvent(cond->event);

   cond->wakens++;

   /* The data structure is done being modified.. I think we can leave the CS now.
    * This would prevent some other thread from receiving the hot potato and then
    * immediately stalling for the critical section.
    * But remember, we were trying to replicate a semantic where this entire
    * scond_signal call was controlled (by the user) by a lock.
    * So in case there's trouble with this, we can move it after SetEvent() */
   LeaveCriticalSection(&cond->cs);

   /* Since there is now at least one pending waken, the potato must be in play */
   SetEvent(cond->hot_potato);

#else
   pthread_cond_signal(&cond->cond);
#endif
}