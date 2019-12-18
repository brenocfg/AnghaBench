#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int (* proc ) (void*) ;void* arg; } ;
struct TYPE_7__ {TYPE_1__ thread; } ;
struct TYPE_8__ {TYPE_2__ u; } ;
struct TYPE_9__ {int /*<<< orphan*/  regs; TYPE_3__ request; } ;
struct TYPE_10__ {TYPE_4__ thread; } ;

/* Variables and functions */
 unsigned long CLONE_UNTRACED ; 
 unsigned long CLONE_VM ; 
 TYPE_5__* current ; 
 int do_fork (unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int kernel_thread(int (*fn)(void *), void * arg, unsigned long flags)
{
	int pid;

	current->thread.request.u.thread.proc = fn;
	current->thread.request.u.thread.arg = arg;
	pid = do_fork(CLONE_VM | CLONE_UNTRACED | flags, 0,
		      &current->thread.regs, 0, NULL, NULL);
	return pid;
}