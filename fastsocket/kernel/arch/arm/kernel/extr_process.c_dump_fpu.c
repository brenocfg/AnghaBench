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
struct user_fp {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  soft; } ;
struct thread_info {int* used_cp; TYPE_1__ fpstate; } ;
struct pt_regs {int dummy; } ;

/* Variables and functions */
 struct thread_info* current_thread_info () ; 
 int /*<<< orphan*/  memcpy (struct user_fp*,int /*<<< orphan*/ *,int) ; 

int dump_fpu (struct pt_regs *regs, struct user_fp *fp)
{
	struct thread_info *thread = current_thread_info();
	int used_math = thread->used_cp[1] | thread->used_cp[2];

	if (used_math)
		memcpy(fp, &thread->fpstate.soft, sizeof (*fp));

	return used_math != 0;
}