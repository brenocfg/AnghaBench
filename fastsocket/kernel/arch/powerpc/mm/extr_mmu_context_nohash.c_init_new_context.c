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
struct TYPE_2__ {scalar_t__ active; int /*<<< orphan*/  id; } ;
struct mm_struct {TYPE_1__ context; } ;

/* Variables and functions */
 int /*<<< orphan*/  MMU_NO_CONTEXT ; 
 int /*<<< orphan*/  pr_hard (char*,struct mm_struct*) ; 

int init_new_context(struct task_struct *t, struct mm_struct *mm)
{
	pr_hard("initing context for mm @%p\n", mm);

	mm->context.id = MMU_NO_CONTEXT;
	mm->context.active = 0;

	return 0;
}