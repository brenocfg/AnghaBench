#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int seen; scalar_t__ pid; int tid; scalar_t__ am_pseudo; struct TYPE_3__* next; } ;
typedef  TYPE_1__ thread_info ;
struct TYPE_4__ {TYPE_1__* head; } ;

/* Variables and functions */
 scalar_t__ debug_on ; 
 int /*<<< orphan*/  del_tthread (int) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 TYPE_2__ thread_head ; 
 scalar_t__ vfork_in_flight ; 
 scalar_t__ vforking_child_pid ; 

__attribute__((used)) static void
update_thread_list (void)
{
  thread_info *p;
  thread_info *chase;

  chase = NULL;
  for (p = thread_head.head; p; p = p->next)
    {
      /* Is this an "unseen" thread which really happens to be a process?
         If so, is it inferior_ptid and is a vfork in flight?  If yes to
         all, then DON'T REMOVE IT!  We're in the midst of moving a vfork
         operation, which is a multiple step thing, to the point where we
         can touch the parent again.  We've most likely stopped to examine
         the child at a late stage in the vfork, and if we're not following
         the child, we'd best not treat the parent as a dead "thread"...
       */
      if ((!p->seen) && p->am_pseudo && vfork_in_flight
	  && (p->pid != vforking_child_pid))
	p->seen = 1;

      if (!p->seen)
	{
	  /* Remove this one
	   */

#ifdef THREAD_DEBUG
	  if (debug_on)
	    printf ("Delete unseen thread: %d \n", p->tid);
#endif
	  del_tthread (p->tid);
	}
    }
}