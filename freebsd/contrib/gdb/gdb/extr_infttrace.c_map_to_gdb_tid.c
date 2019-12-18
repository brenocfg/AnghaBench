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
struct TYPE_4__ {scalar_t__ tid; scalar_t__ pid; scalar_t__ am_pseudo; struct TYPE_4__* next; } ;
typedef  TYPE_1__ thread_info ;
typedef  scalar_t__ lwpid_t ;
struct TYPE_6__ {TYPE_1__* head; } ;
struct TYPE_5__ {TYPE_1__* head; } ;

/* Variables and functions */
 TYPE_3__ deleted_threads ; 
 TYPE_2__ thread_head ; 

__attribute__((used)) static lwpid_t
map_to_gdb_tid (lwpid_t real_tid)
{
  thread_info *p;

  for (p = thread_head.head; p; p = p->next)
    {
      if (p->tid == real_tid)
	{
	  if (p->am_pseudo)
	    return p->pid;
	  else
	    return real_tid;
	}
    }

  for (p = deleted_threads.head; p; p = p->next)
    {
      if (p->tid == real_tid)
	if (p->am_pseudo)
	  return p->pid;	/* Error? */
	else
	  return real_tid;
    }

  return 0;			/* Error?  Never heard of this thread! */
}