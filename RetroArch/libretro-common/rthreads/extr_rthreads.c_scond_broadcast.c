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
struct TYPE_3__ {scalar_t__ waiters; scalar_t__ wakens; int /*<<< orphan*/  cond; int /*<<< orphan*/  hot_potato; int /*<<< orphan*/  event; } ;
typedef  TYPE_1__ scond_t ;

/* Variables and functions */
 int /*<<< orphan*/  SetEvent (int /*<<< orphan*/ ) ; 
 int pthread_cond_broadcast (int /*<<< orphan*/ *) ; 

int scond_broadcast(scond_t *cond)
{
#ifdef USE_WIN32_THREADS
   /* remember: we currently have mutex */
   if (cond->waiters == 0)
      return 0;

   /* awaken everything which is currently queued up */
   if (cond->wakens == 0)
      SetEvent(cond->event);
   cond->wakens = cond->waiters;

   /* Since there is now at least one pending waken, the potato must be in play */
   SetEvent(cond->hot_potato);

   return 0;
#else
   return pthread_cond_broadcast(&cond->cond);
#endif
}