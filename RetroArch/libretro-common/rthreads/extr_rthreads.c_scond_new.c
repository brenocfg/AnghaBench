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
struct TYPE_4__ {int /*<<< orphan*/  cond; int /*<<< orphan*/ * head; scalar_t__ wakens; scalar_t__ waiters; int /*<<< orphan*/  cs; void* event; void* hot_potato; } ;
typedef  TYPE_1__ scond_t ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (void*) ; 
 void* CreateEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  InitializeCriticalSection (int /*<<< orphan*/ *) ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 scalar_t__ pthread_cond_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

scond_t *scond_new(void)
{
   scond_t      *cond = (scond_t*)calloc(1, sizeof(*cond));

   if (!cond)
      return NULL;

#ifdef USE_WIN32_THREADS

   /* This is very complex because recreating condition variable semantics
    * with Win32 parts is not easy.
    *
    * The main problem is that a condition variable can't be used to
    * "pre-wake" a thread (it will get wakened only after it's waited).
    *
    * Whereas a win32 event can pre-wake a thread (the event will be set
    * in advance, so a 'waiter' won't even have to wait on it).
    *
    * Keep in mind a condition variable can apparently pre-wake a thread,
    * insofar as spurious wakeups are always possible,
    * but nobody will be expecting this and it does not need to be simulated.
    *
    * Moreover, we won't be doing this, because it counts as a spurious wakeup
    * -- someone else with a genuine claim must get wakened, in any case.
    *
    * Therefore we choose to wake only one of the correct waiting threads.
    * So at the very least, we need to do something clever. But there's
    * bigger problems.
    * We don't even have a straightforward way in win32 to satisfy
    * pthread_cond_wait's atomicity requirement. The bulk of this
    * algorithm is solving that.
    *
    * Note: We might could simplify this using vista+ condition variables,
    * but we wanted an XP compatible solution. */
   cond->event = CreateEvent(NULL, FALSE, FALSE, NULL);
   if (!cond->event)
      goto error;
   cond->hot_potato = CreateEvent(NULL, FALSE, FALSE, NULL);
   if (!cond->hot_potato)
   {
      CloseHandle(cond->event);
      goto error;
   }

   InitializeCriticalSection(&cond->cs);
   cond->waiters = cond->wakens = 0;
   cond->head = NULL;

#else
   if (pthread_cond_init(&cond->cond, NULL) != 0)
      goto error;
#endif

   return cond;

error:
   free(cond);
   return NULL;
}