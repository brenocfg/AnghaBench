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
struct TYPE_2__ {unsigned long esp; } ;
struct task_struct {scalar_t__ state; TYPE_1__ thread; } ;

/* Variables and functions */
 scalar_t__ TASK_RUNNING ; 
 struct task_struct* current ; 
 int /*<<< orphan*/  in_sched_functions (unsigned long) ; 

unsigned long get_wchan(struct task_struct *p)
{
#if 0
	/* YURGH. TODO. */

        unsigned long ebp, esp, eip;
        unsigned long stack_page;
        int count = 0;
        if (!p || p == current || p->state == TASK_RUNNING)
                return 0;
        stack_page = (unsigned long)p;
        esp = p->thread.esp;
        if (!stack_page || esp < stack_page || esp > 8188+stack_page)
                return 0;
        /* include/asm-i386/system.h:switch_to() pushes ebp last. */
        ebp = *(unsigned long *) esp;
        do {
                if (ebp < stack_page || ebp > 8184+stack_page)
                        return 0;
                eip = *(unsigned long *) (ebp+4);
		if (!in_sched_functions(eip))
			return eip;
                ebp = *(unsigned long *) ebp;
        } while (count++ < 16);
#endif
        return 0;
}