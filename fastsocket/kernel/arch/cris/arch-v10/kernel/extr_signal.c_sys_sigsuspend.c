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
struct pt_regs {int dummy; } ;
typedef  int /*<<< orphan*/  old_sigset_t ;
struct TYPE_4__ {int /*<<< orphan*/  state; TYPE_1__* sighand; int /*<<< orphan*/  blocked; int /*<<< orphan*/  saved_sigmask; } ;
struct TYPE_3__ {int /*<<< orphan*/  siglock; } ;

/* Variables and functions */
 int ERESTARTNOHAND ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TIF_RESTORE_SIGMASK ; 
 int /*<<< orphan*/  _BLOCKABLE ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  recalc_sigpending () ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_thread_flag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  siginitset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

int sys_sigsuspend(old_sigset_t mask, long r11, long r12, long r13, long mof,
	long srp, struct pt_regs *regs)
{
	mask &= _BLOCKABLE;
	spin_lock_irq(&current->sighand->siglock);
	current->saved_sigmask = current->blocked;
	siginitset(&current->blocked, mask);
	recalc_sigpending();
	spin_unlock_irq(&current->sighand->siglock);
	current->state = TASK_INTERRUPTIBLE;
	schedule();
	set_thread_flag(TIF_RESTORE_SIGMASK);
	return -ERESTARTNOHAND;
}