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
struct TYPE_4__ {scalar_t__ tid; int pid; struct TYPE_4__* next; } ;
typedef  TYPE_1__ thread_info ;
typedef  scalar_t__ lwpid_t ;
struct TYPE_6__ {TYPE_1__* head; } ;
struct TYPE_5__ {TYPE_1__* head; } ;

/* Variables and functions */
 TYPE_3__ deleted_threads ; 
 TYPE_2__ thread_head ; 

__attribute__((used)) static int
get_pid_for (lwpid_t tid)
{
  thread_info *p;

  for (p = thread_head.head; p; p = p->next)
    {
      if (p->tid == tid)
	{
	  return p->pid;
	}
    }

  for (p = deleted_threads.head; p; p = p->next)
    {
      if (p->tid == tid)
	{
	  return p->pid;
	}
    }

  return 0;
}