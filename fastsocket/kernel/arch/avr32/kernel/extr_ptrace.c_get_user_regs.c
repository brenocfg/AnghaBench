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
struct task_struct {int dummy; } ;
struct pt_regs {int dummy; } ;

/* Variables and functions */
 scalar_t__ THREAD_SIZE ; 
 scalar_t__ task_stack_page (struct task_struct*) ; 

__attribute__((used)) static struct pt_regs *get_user_regs(struct task_struct *tsk)
{
	return (struct pt_regs *)((unsigned long)task_stack_page(tsk) +
				  THREAD_SIZE - sizeof(struct pt_regs));
}