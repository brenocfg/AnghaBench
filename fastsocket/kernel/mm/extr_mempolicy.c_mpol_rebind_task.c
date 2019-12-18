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
struct task_struct {int /*<<< orphan*/  mempolicy; } ;
typedef  int /*<<< orphan*/  nodemask_t ;
typedef  enum mpol_rebind_step { ____Placeholder_mpol_rebind_step } mpol_rebind_step ;

/* Variables and functions */
 int /*<<< orphan*/  mpol_rebind_policy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 

void mpol_rebind_task(struct task_struct *tsk, const nodemask_t *new,
			enum mpol_rebind_step step)
{
	mpol_rebind_policy(tsk->mempolicy, new, step);
}