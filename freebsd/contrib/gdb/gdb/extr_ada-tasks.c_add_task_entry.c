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
struct task_entry {int task_num; int known_tasks_index; scalar_t__ stack_per; struct task_entry* next_task; void* task_id; } ;

/* Variables and functions */
 int highest_task_num ; 
 struct task_entry* task_list ; 
 struct task_entry* xmalloc (int) ; 

__attribute__((used)) static int
add_task_entry (void *p_task_id, int index)
{
  struct task_entry *new_task_entry = NULL;
  struct task_entry *pt;

  highest_task_num++;
  new_task_entry = xmalloc (sizeof (struct task_entry));
  new_task_entry->task_num = highest_task_num;
  new_task_entry->task_id = p_task_id;
  new_task_entry->known_tasks_index = index;
  new_task_entry->next_task = NULL;
  pt = task_list;
  if (pt)
    {
      while (pt->next_task)
	pt = pt->next_task;
      pt->next_task = new_task_entry;
      pt->stack_per = 0;
    }
  else
    task_list = new_task_entry;
  return new_task_entry->task_num;
}