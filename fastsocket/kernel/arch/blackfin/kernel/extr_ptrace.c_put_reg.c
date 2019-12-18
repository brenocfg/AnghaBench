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
struct TYPE_2__ {unsigned long usp; } ;
struct task_struct {TYPE_1__ thread; } ;
struct pt_regs {unsigned long retx; unsigned long pc; unsigned long usp; } ;

/* Variables and functions */
#define  PT_PC 130 
#define  PT_RETX 129 
#define  PT_USP 128 
 int THREAD_SIZE ; 
 scalar_t__ task_stack_page (struct task_struct*) ; 

__attribute__((used)) static inline int
put_reg(struct task_struct *task, int regno, unsigned long data)
{
	char *reg_ptr;

	struct pt_regs *regs =
	    (struct pt_regs *)((unsigned long)task_stack_page(task) +
			       (THREAD_SIZE - sizeof(struct pt_regs)));
	reg_ptr = (char *)regs;

	switch (regno) {
	case PT_PC:
		/*********************************************************************/
		/* At this point the kernel is most likely in exception.             */
		/* The RETX register will be used to populate the pc of the process. */
		/*********************************************************************/
		regs->retx = data;
		regs->pc = data;
		break;
	case PT_RETX:
		break;		/* regs->retx = data; break; */
	case PT_USP:
		regs->usp = data;
		task->thread.usp = data;
		break;
	default:
		if (regno <= 216)
			*(long *)(reg_ptr + regno) = data;
	}
	return 0;
}