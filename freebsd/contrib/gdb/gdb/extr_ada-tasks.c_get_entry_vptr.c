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
struct task_entry {int task_num; struct task_entry* next_task; } ;

/* Variables and functions */
 struct task_entry* task_list ; 

__attribute__((used)) static struct task_entry *
get_entry_vptr (int p_task_num)
{
  struct task_entry *pt;

  pt = task_list;
  while (pt)
    {
      if (pt->task_num == p_task_num)
	return pt;
      pt = pt->next_task;
    }
  return NULL;
}