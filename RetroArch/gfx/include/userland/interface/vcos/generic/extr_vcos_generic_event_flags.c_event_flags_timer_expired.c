#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VCOS_THREAD_T ;
struct TYPE_8__ {struct TYPE_8__* next; int /*<<< orphan*/ * thread; TYPE_3__* flags; } ;
typedef  TYPE_2__ VCOS_EVENT_WAITER_T ;
struct TYPE_7__ {TYPE_2__* tail; TYPE_2__* head; } ;
struct TYPE_9__ {int /*<<< orphan*/  lock; TYPE_1__ waiters; } ;
typedef  TYPE_3__ VCOS_EVENT_FLAGS_T ;

/* Variables and functions */
 int /*<<< orphan*/  _vcos_thread_sem_post (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_assert (TYPE_3__*) ; 
 int /*<<< orphan*/  vcos_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_3__* waiter_list_valid (TYPE_3__*) ; 

__attribute__((used)) static void event_flags_timer_expired(void *cxt)
{
   VCOS_EVENT_WAITER_T *waitreq = (VCOS_EVENT_WAITER_T *)cxt;
   VCOS_EVENT_FLAGS_T *flags = waitreq->flags;
   VCOS_EVENT_WAITER_T **plist;
   VCOS_EVENT_WAITER_T *prev = NULL;
   VCOS_THREAD_T *thread = 0;

   vcos_assert(flags);

   vcos_mutex_lock(&flags->lock);

   /* walk the list of waiting threads on this event group, and remove
    * the one that has expired.
    *
    * FIXME: could use doubly-linked list if lots of threads are found
    * to be waiting on a single event flag instance.
    */
   plist = &flags->waiters.head;
   while (*plist != NULL)
   {
      if (*plist == waitreq)
      {
         int at_end;
         /* found it */
         thread = (*plist)->thread;
         at_end = ((*plist)->next == NULL);

         /* link past */
         *plist = (*plist)->next;
         if (at_end)
            flags->waiters.tail = prev;

         break;
      }
      prev = *plist;
      plist = &(*plist)->next;
   }
   vcos_assert(waiter_list_valid(flags));

   vcos_mutex_unlock(&flags->lock);

   if (thread)
   {
      _vcos_thread_sem_post(thread);
   }
}