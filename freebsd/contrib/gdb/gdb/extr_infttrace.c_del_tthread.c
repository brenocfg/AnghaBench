#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ tid; int terminated; struct TYPE_4__* next_pseudo; scalar_t__ am_pseudo; struct TYPE_4__* next; } ;
typedef  TYPE_1__ thread_info ;
typedef  scalar_t__ lwpid_t ;
struct TYPE_6__ {TYPE_1__* head_pseudo; int /*<<< orphan*/  count; TYPE_1__* head; } ;
struct TYPE_5__ {scalar_t__ count; TYPE_1__* head; TYPE_1__* head_pseudo; } ;

/* Variables and functions */
 scalar_t__ debug_on ; 
 TYPE_3__ deleted_threads ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  printf (char*,scalar_t__) ; 
 TYPE_2__ thread_head ; 

__attribute__((used)) static void
del_tthread (lwpid_t tid)
{
  thread_info *p;
  thread_info *chase;

  if (thread_head.count <= 0)
    {
      error ("Internal error in thread database.");
      return;
    }

  chase = NULL;
  for (p = thread_head.head; p; p = p->next)
    {
      if (p->tid == tid)
	{

#ifdef THREAD_DEBUG
	  if (debug_on)
	    printf ("Delete here: %d \n", tid);
#endif

	  if (p->am_pseudo)
	    {
	      /*
	       * Deleting a main thread is ok if we're doing
	       * a parent-follow on a child; this is odd but
	       * not wrong.  It apparently _doesn't_ happen
	       * on the child-follow, as we don't just delete
	       * the pseudo while keeping the rest of the
	       * threads around--instead, we clear out the whole
	       * thread list at once.
	       */
	      thread_info *q;
	      thread_info *q_chase;

	      q_chase = NULL;
	      for (q = thread_head.head_pseudo; q; q = q->next)
		{
		  if (q == p)
		    {
		      /* Remove from pseudo list.
		       */
		      if (q_chase == NULL)
			thread_head.head_pseudo = p->next_pseudo;
		      else
			q_chase->next = p->next_pseudo;
		    }
		  else
		    q_chase = q;
		}
	    }

	  /* Remove from live list.
	   */
	  thread_head.count--;

	  if (NULL == chase)
	    thread_head.head = p->next;
	  else
	    chase->next = p->next;

	  /* Add to deleted thread list.
	   */
	  p->next = deleted_threads.head;
	  deleted_threads.head = p;
	  deleted_threads.count++;
	  if (p->am_pseudo)
	    {
	      p->next_pseudo = deleted_threads.head_pseudo;
	      deleted_threads.head_pseudo = p;
	    }
	  p->terminated = 1;

	  return;
	}

      else
	chase = p;
    }
}