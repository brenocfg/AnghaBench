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
struct TYPE_4__ {scalar_t__ tid; scalar_t__ pid; struct TYPE_4__* next_pseudo; struct TYPE_4__* next; } ;
typedef  TYPE_1__ thread_info ;
typedef  scalar_t__ lwpid_t ;
struct TYPE_6__ {TYPE_1__* head_pseudo; TYPE_1__* head; } ;
struct TYPE_5__ {TYPE_1__* head_pseudo; TYPE_1__* head; } ;

/* Variables and functions */
 TYPE_3__ deleted_threads ; 
 TYPE_2__ thread_head ; 

__attribute__((used)) static lwpid_t
map_from_gdb_tid (lwpid_t gdb_tid)
{
  thread_info *p;

  /* First assume gdb_tid really is a tid, and try to find a
   * matching entry on the threads list.
   */
  for (p = thread_head.head; p; p = p->next)
    {
      if (p->tid == gdb_tid)
	return gdb_tid;
    }

  /* It doesn't appear to be a tid; perhaps it's really a pid?
   * Try to find a "pseudo" thread entry on the threads list.
   */
  for (p = thread_head.head_pseudo; p != NULL; p = p->next_pseudo)
    {
      if (p->pid == gdb_tid)
	return p->tid;
    }

  /* Perhaps it's the tid of a deleted thread we may still
   * have some knowledge of?
   */
  for (p = deleted_threads.head; p; p = p->next)
    {
      if (p->tid == gdb_tid)
	return gdb_tid;
    }

  /* Or perhaps it's the pid of a deleted process we may still
   * have knowledge of?
   */
  for (p = deleted_threads.head_pseudo; p != NULL; p = p->next_pseudo)
    {
      if (p->pid == gdb_tid)
	return p->tid;
    }

  return 0;			/* Error? */
}