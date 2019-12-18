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
struct user_context {int dummy; } ;
struct TYPE_2__ {struct user_context* user; } ;
struct task_struct {TYPE_1__ thread; } ;

/* Variables and functions */
 int PT__END ; 

__attribute__((used)) static inline long get_reg(struct task_struct *task, int regno)
{
	struct user_context *user = task->thread.user;

	if (regno < 0 || regno >= PT__END)
		return 0;

	return ((unsigned long *) user)[regno];
}