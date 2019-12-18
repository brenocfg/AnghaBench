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
struct TYPE_2__ {struct task_struct* saved_task; } ;
struct task_struct {TYPE_1__ thread; } ;

/* Variables and functions */
 struct task_struct* current ; 
 int /*<<< orphan*/  switch_to (struct task_struct*,struct task_struct*,struct task_struct*) ; 

__attribute__((used)) static void stack_proc(void *arg)
{
	struct task_struct *from = current, *to = arg;

	to->thread.saved_task = from;
	switch_to(from, to, from);
}