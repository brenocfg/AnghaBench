#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  TYPE_1__* proc_t ;
struct TYPE_3__ {int /*<<< orphan*/  p_memstat_state; int /*<<< orphan*/  task; } ;

/* Variables and functions */
 int /*<<< orphan*/  P_MEMSTAT_SUSPENDED ; 
 int /*<<< orphan*/  memorystatus_get_task_page_counts (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memorystatus_suspended_count ; 
 int /*<<< orphan*/  proc_list_lock () ; 
 int /*<<< orphan*/  proc_list_unlock () ; 

void
memorystatus_on_suspend(proc_t p)
{
#if CONFIG_FREEZE
	uint32_t pages;
	memorystatus_get_task_page_counts(p->task, &pages, NULL, NULL);
#endif
	proc_list_lock();
#if CONFIG_FREEZE
	memorystatus_suspended_count++;
#endif
	p->p_memstat_state |= P_MEMSTAT_SUSPENDED;
	proc_list_unlock();
}