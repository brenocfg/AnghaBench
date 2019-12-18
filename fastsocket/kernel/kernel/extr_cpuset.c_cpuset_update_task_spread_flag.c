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
struct task_struct {int /*<<< orphan*/  flags; } ;
struct cpuset {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PF_SPREAD_PAGE ; 
 int /*<<< orphan*/  PF_SPREAD_SLAB ; 
 scalar_t__ is_spread_page (struct cpuset*) ; 
 scalar_t__ is_spread_slab (struct cpuset*) ; 

__attribute__((used)) static void cpuset_update_task_spread_flag(struct cpuset *cs,
					struct task_struct *tsk)
{
	if (is_spread_page(cs))
		tsk->flags |= PF_SPREAD_PAGE;
	else
		tsk->flags &= ~PF_SPREAD_PAGE;
	if (is_spread_slab(cs))
		tsk->flags |= PF_SPREAD_SLAB;
	else
		tsk->flags &= ~PF_SPREAD_SLAB;
}