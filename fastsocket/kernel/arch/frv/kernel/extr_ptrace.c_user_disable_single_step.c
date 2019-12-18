#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* frame0; } ;
struct task_struct {TYPE_2__ thread; } ;
struct TYPE_3__ {int /*<<< orphan*/  __status; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG__STATUS_STEP ; 

void user_disable_single_step(struct task_struct *child)
{
	child->thread.frame0->__status &= ~REG__STATUS_STEP;
}