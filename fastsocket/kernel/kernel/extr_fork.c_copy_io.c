#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct task_struct {TYPE_1__* io_context; } ;
struct io_context {int /*<<< orphan*/  ioprio; } ;
struct TYPE_5__ {struct io_context* io_context; } ;
struct TYPE_4__ {int /*<<< orphan*/  ioprio; } ;

/* Variables and functions */
 unsigned long CLONE_IO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_1__* alloc_io_context (int /*<<< orphan*/ ,int) ; 
 TYPE_2__* current ; 
 TYPE_1__* ioc_task_link (struct io_context*) ; 
 scalar_t__ ioprio_valid (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int copy_io(unsigned long clone_flags, struct task_struct *tsk)
{
#ifdef CONFIG_BLOCK
	struct io_context *ioc = current->io_context;

	if (!ioc)
		return 0;
	/*
	 * Share io context with parent, if CLONE_IO is set
	 */
	if (clone_flags & CLONE_IO) {
		tsk->io_context = ioc_task_link(ioc);
		if (unlikely(!tsk->io_context))
			return -ENOMEM;
	} else if (ioprio_valid(ioc->ioprio)) {
		tsk->io_context = alloc_io_context(GFP_KERNEL, -1);
		if (unlikely(!tsk->io_context))
			return -ENOMEM;

		tsk->io_context->ioprio = ioc->ioprio;
	}
#endif
	return 0;
}