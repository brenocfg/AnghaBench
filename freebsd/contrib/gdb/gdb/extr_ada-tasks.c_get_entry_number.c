#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct task_entry {void* task_id; int task_num; struct task_entry* next_task; } ;

/* Variables and functions */
 struct task_entry* task_list ; 

int
get_entry_number (void *p_task_id)
{
  struct task_entry *pt;

  pt = task_list;
  while (pt != NULL)
    {
      if (pt->task_id == p_task_id)
	return pt->task_num;
      pt = pt->next_task;
    }
  return 0;
}