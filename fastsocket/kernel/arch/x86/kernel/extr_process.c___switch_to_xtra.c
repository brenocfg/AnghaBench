#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct tss_struct {int /*<<< orphan*/  io_bitmap; } ;
struct thread_struct {int /*<<< orphan*/  io_bitmap_max; int /*<<< orphan*/  io_bitmap_ptr; int /*<<< orphan*/  debugreg7; int /*<<< orphan*/  debugreg6; int /*<<< orphan*/  debugreg3; int /*<<< orphan*/  debugreg2; int /*<<< orphan*/  debugreg1; int /*<<< orphan*/  debugreg0; } ;
struct task_struct {struct thread_struct thread; } ;

/* Variables and functions */
 unsigned long DEBUGCTLMSR_BTF ; 
 int /*<<< orphan*/  TIF_BLOCKSTEP ; 
 int /*<<< orphan*/  TIF_DEBUG ; 
 int /*<<< orphan*/  TIF_IO_BITMAP ; 
 int /*<<< orphan*/  TIF_NOTSC ; 
 unsigned long get_debugctlmsr () ; 
 int /*<<< orphan*/  hard_disable_TSC () ; 
 int /*<<< orphan*/  hard_enable_TSC () ; 
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  propagate_user_return_notify (struct task_struct*,struct task_struct*) ; 
 int /*<<< orphan*/  set_debugreg (int /*<<< orphan*/ ,int) ; 
 int test_tsk_thread_flag (struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_debugctlmsr (unsigned long) ; 

void __switch_to_xtra(struct task_struct *prev_p, struct task_struct *next_p,
		      struct tss_struct *tss)
{
	struct thread_struct *prev, *next;

	prev = &prev_p->thread;
	next = &next_p->thread;

	if (test_tsk_thread_flag(next_p, TIF_DEBUG)) {
		set_debugreg(next->debugreg0, 0);
		set_debugreg(next->debugreg1, 1);
		set_debugreg(next->debugreg2, 2);
		set_debugreg(next->debugreg3, 3);
		/* no 4 and 5 */
		set_debugreg(next->debugreg6, 6);
		set_debugreg(next->debugreg7, 7);
	}

	if (test_tsk_thread_flag(prev_p, TIF_BLOCKSTEP) ^
	    test_tsk_thread_flag(next_p, TIF_BLOCKSTEP)) {
		unsigned long debugctl = get_debugctlmsr();

		debugctl &= ~DEBUGCTLMSR_BTF;
		if (test_tsk_thread_flag(next_p, TIF_BLOCKSTEP))
			debugctl |= DEBUGCTLMSR_BTF;

		update_debugctlmsr(debugctl);
	}

	if (test_tsk_thread_flag(prev_p, TIF_NOTSC) ^
	    test_tsk_thread_flag(next_p, TIF_NOTSC)) {
		/* prev and next are different */
		if (test_tsk_thread_flag(next_p, TIF_NOTSC))
			hard_disable_TSC();
		else
			hard_enable_TSC();
	}

	if (test_tsk_thread_flag(next_p, TIF_IO_BITMAP)) {
		/*
		 * Copy the relevant range of the IO bitmap.
		 * Normally this is 128 bytes or less:
		 */
		memcpy(tss->io_bitmap, next->io_bitmap_ptr,
		       max(prev->io_bitmap_max, next->io_bitmap_max));
	} else if (test_tsk_thread_flag(prev_p, TIF_IO_BITMAP)) {
		/*
		 * Clear any possible leftover bits:
		 */
		memset(tss->io_bitmap, 0xff, prev->io_bitmap_max);
	}
	propagate_user_return_notify(prev_p, next_p);
}