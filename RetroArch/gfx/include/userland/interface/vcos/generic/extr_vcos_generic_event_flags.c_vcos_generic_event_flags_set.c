#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int VCOS_UNSIGNED ;
typedef  scalar_t__ VCOS_OPTION ;
struct TYPE_9__ {int requested_events; scalar_t__ op; int actual_events; struct TYPE_9__* next; int /*<<< orphan*/  thread; int /*<<< orphan*/  return_status; } ;
typedef  TYPE_2__ VCOS_EVENT_WAITER_T ;
struct TYPE_8__ {TYPE_2__* tail; TYPE_2__* head; } ;
struct TYPE_10__ {int events; int /*<<< orphan*/  lock; TYPE_1__ waiters; } ;
typedef  TYPE_3__ VCOS_EVENT_FLAGS_T ;

/* Variables and functions */
 scalar_t__ VCOS_AND ; 
 int VCOS_CONSUME ; 
 scalar_t__ VCOS_OR ; 
 int /*<<< orphan*/  VCOS_SUCCESS ; 
 int /*<<< orphan*/  _vcos_thread_sem_post (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_assert (TYPE_3__*) ; 
 int /*<<< orphan*/  vcos_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_3__* waiter_list_valid (TYPE_3__*) ; 

void vcos_generic_event_flags_set(VCOS_EVENT_FLAGS_T *flags,
                                  VCOS_UNSIGNED bitmask,
                                  VCOS_OPTION op)
{
   vcos_assert(flags);
   vcos_mutex_lock(&flags->lock);
   if (op == VCOS_OR)
   {
      flags->events |= bitmask;
   }
   else if (op == VCOS_AND)
   {
      flags->events &= bitmask;
   }
   else
   {
      vcos_assert(0);
   }

   /* Now wake up any threads that have now become signalled. */
   if (flags->waiters.head != NULL)
   {
      VCOS_UNSIGNED consumed_events = 0;
      VCOS_EVENT_WAITER_T **pcurrent_waiter = &flags->waiters.head;
      VCOS_EVENT_WAITER_T *prev_waiter = NULL;

      /* Walk the chain of tasks suspend on this event flag group to determine
       * if any of their requests can be satisfied.
       */
      while ((*pcurrent_waiter) != NULL)
      {
         VCOS_EVENT_WAITER_T *curr_waiter = *pcurrent_waiter;

         /* Determine if this request has been satisfied */

         /* First, find the event flags in common. */
         VCOS_UNSIGNED waiter_satisfied = flags->events & curr_waiter->requested_events;

         /* Second, determine if all the event flags must match */
         if (curr_waiter->op & VCOS_AND)
         {
            /* All requested events must be present */
            waiter_satisfied = (waiter_satisfied == curr_waiter->requested_events);
         }

         /* Wake this one up? */
         if (waiter_satisfied)
         {

            if (curr_waiter->op & VCOS_CONSUME)
            {
               consumed_events |= curr_waiter->requested_events;
            }

            /* remove this block from the list, taking care at the end */
            *pcurrent_waiter = curr_waiter->next;
            if (curr_waiter->next == NULL)
               flags->waiters.tail = prev_waiter;

            vcos_assert(waiter_list_valid(flags));

            curr_waiter->return_status = VCOS_SUCCESS;
            curr_waiter->actual_events = flags->events;

            _vcos_thread_sem_post(curr_waiter->thread);
         }
         else
         {
            /* move to next element in the list */
            prev_waiter = *pcurrent_waiter;
            pcurrent_waiter = &(curr_waiter->next);
         }
      }

      flags->events &= ~consumed_events;

   }

   vcos_mutex_unlock(&flags->lock);
}