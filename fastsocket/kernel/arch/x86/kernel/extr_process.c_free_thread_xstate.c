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
struct TYPE_2__ {int /*<<< orphan*/  xstate; } ;
struct task_struct {TYPE_1__ thread; } ;
struct fpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fpu_free (struct fpu*) ; 

void free_thread_xstate(struct task_struct *tsk)
{
	fpu_free((struct fpu *)&tsk->thread.xstate);
}