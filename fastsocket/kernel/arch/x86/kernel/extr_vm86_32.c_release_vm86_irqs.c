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
struct task_struct {int dummy; } ;
struct TYPE_2__ {struct task_struct* tsk; } ;

/* Variables and functions */
 int FIRST_VM86_IRQ ; 
 int LAST_VM86_IRQ ; 
 int /*<<< orphan*/  free_vm86_irq (int) ; 
 TYPE_1__* vm86_irqs ; 

void release_vm86_irqs(struct task_struct *task)
{
	int i;
	for (i = FIRST_VM86_IRQ ; i <= LAST_VM86_IRQ; i++)
	    if (vm86_irqs[i].tsk == task)
		free_vm86_irq(i);
}