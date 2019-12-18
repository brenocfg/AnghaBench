#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * next; } ;
struct timer_list {int start_pid; int /*<<< orphan*/  lockdep_map; int /*<<< orphan*/  start_comm; int /*<<< orphan*/ * start_site; int /*<<< orphan*/  base; TYPE_1__ entry; } ;
struct lock_class_key {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TASK_COMM_LEN ; 
 int /*<<< orphan*/  __raw_get_cpu_var (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_init_map (int /*<<< orphan*/ *,char const*,struct lock_class_key*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tvec_bases ; 

__attribute__((used)) static void __init_timer(struct timer_list *timer,
			 const char *name,
			 struct lock_class_key *key)
{
	timer->entry.next = NULL;
	timer->base = __raw_get_cpu_var(tvec_bases);
#ifdef CONFIG_TIMER_STATS
	timer->start_site = NULL;
	timer->start_pid = -1;
	memset(timer->start_comm, 0, TASK_COMM_LEN);
#endif
	lockdep_init_map(&timer->lockdep_map, name, key, 0);
}