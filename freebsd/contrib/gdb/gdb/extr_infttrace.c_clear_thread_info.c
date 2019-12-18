#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* next; } ;
typedef  TYPE_1__ thread_info ;
struct TYPE_7__ {scalar_t__ count; int /*<<< orphan*/ * head_pseudo; TYPE_1__* head; } ;
struct TYPE_6__ {scalar_t__ count; int /*<<< orphan*/ * head_pseudo; TYPE_1__* head; } ;

/* Variables and functions */
 scalar_t__ debug_on ; 
 TYPE_4__ deleted_threads ; 
 scalar_t__ more_events_left ; 
 int /*<<< orphan*/  printf (char*) ; 
 TYPE_3__ thread_head ; 
 int /*<<< orphan*/  xfree (TYPE_1__*) ; 

__attribute__((used)) static void
clear_thread_info (void)
{
  thread_info *p;
  thread_info *q;

#ifdef THREAD_DEBUG
  if (debug_on)
    printf ("Clearing all thread info\n");
#endif

  p = thread_head.head;
  while (p)
    {
      q = p;
      p = p->next;
      xfree (q);
    }

  thread_head.head = NULL;
  thread_head.head_pseudo = NULL;
  thread_head.count = 0;

  p = deleted_threads.head;
  while (p)
    {
      q = p;
      p = p->next;
      xfree (q);
    }

  deleted_threads.head = NULL;
  deleted_threads.head_pseudo = NULL;
  deleted_threads.count = 0;

  /* No threads, so can't have pending events.
   */
  more_events_left = 0;
}