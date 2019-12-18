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
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ tid; struct TYPE_5__* next; } ;
typedef  TYPE_1__ thread_info ;
typedef  scalar_t__ lwpid_t ;
struct TYPE_7__ {TYPE_1__* head; } ;
struct TYPE_6__ {TYPE_1__* head; } ;

/* Variables and functions */
 TYPE_4__ deleted_threads ; 
 TYPE_2__ thread_head ; 

__attribute__((used)) static thread_info *
find_thread_info (lwpid_t tid)
{
  thread_info *p;

  for (p = thread_head.head; p; p = p->next)
    {
      if (p->tid == tid)
	{
	  return p;
	}
    }

  for (p = deleted_threads.head; p; p = p->next)
    {
      if (p->tid == tid)
	{
	  return p;
	}
    }

  return NULL;
}