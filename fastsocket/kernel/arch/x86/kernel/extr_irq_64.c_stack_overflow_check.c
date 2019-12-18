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
typedef  scalar_t__ u64 ;
struct thread_info {int dummy; } ;
struct pt_regs {scalar_t__ sp; } ;
struct TYPE_3__ {int /*<<< orphan*/  comm; } ;

/* Variables and functions */
 scalar_t__ THREAD_SIZE ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  task_stack_page (TYPE_1__*) ; 

__attribute__((used)) static inline void stack_overflow_check(struct pt_regs *regs)
{
#ifdef CONFIG_DEBUG_STACKOVERFLOW
	u64 curbase = (u64)task_stack_page(current);

	WARN_ONCE(regs->sp >= curbase &&
		  regs->sp <= curbase + THREAD_SIZE &&
		  regs->sp <  curbase + sizeof(struct thread_info) +
					sizeof(struct pt_regs) + 128,

		  "do_IRQ: %s near stack overflow (cur:%Lx,sp:%lx)\n",
			current->comm, curbase, regs->sp);
#endif
}