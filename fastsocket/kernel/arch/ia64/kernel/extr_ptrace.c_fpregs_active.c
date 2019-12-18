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
struct user_regset {int dummy; } ;
struct TYPE_2__ {int flags; } ;
struct task_struct {TYPE_1__ thread; } ;

/* Variables and functions */
 int IA64_THREAD_FPH_VALID ; 

__attribute__((used)) static int
fpregs_active(struct task_struct *target, const struct user_regset *regset)
{
	return (target->thread.flags & IA64_THREAD_FPH_VALID) ? 128 : 32;
}