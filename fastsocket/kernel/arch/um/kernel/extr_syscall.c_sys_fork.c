#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  regs; } ;
struct TYPE_4__ {int forking; TYPE_2__ regs; } ;
struct TYPE_6__ {TYPE_1__ thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGCHLD ; 
 int /*<<< orphan*/  UPT_SP (int /*<<< orphan*/ *) ; 
 TYPE_3__* current ; 
 long do_fork (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

long sys_fork(void)
{
	long ret;

	current->thread.forking = 1;
	ret = do_fork(SIGCHLD, UPT_SP(&current->thread.regs.regs),
		      &current->thread.regs, 0, NULL, NULL);
	current->thread.forking = 0;
	return ret;
}