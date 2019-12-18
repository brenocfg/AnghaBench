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
struct TYPE_2__ {int /*<<< orphan*/  xstate; } ;
struct task_struct {TYPE_1__ thread; } ;
struct fpu {int dummy; } ;

/* Variables and functions */
 int fpu_alloc (struct fpu*) ; 
 scalar_t__ fpu_allocated (struct fpu*) ; 
 int /*<<< orphan*/  fpu_copy (struct fpu*,struct fpu*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int arch_dup_task_struct(struct task_struct *dst, struct task_struct *src)
{
	int ret;

	*dst = *src;
	if (fpu_allocated((struct fpu *)&src->thread.xstate)) {
		memset(&dst->thread.xstate, 0, sizeof(dst->thread.xstate));
		ret = fpu_alloc((struct fpu *)&dst->thread.xstate);
		if (ret)
			return ret;
		fpu_copy((struct fpu *)&dst->thread.xstate, (struct fpu *)&src->thread.xstate);
	}
	return 0;
}