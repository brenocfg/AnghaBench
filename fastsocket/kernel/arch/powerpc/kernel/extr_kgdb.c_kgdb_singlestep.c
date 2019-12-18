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
struct thread_info {int dummy; } ;
struct pt_regs {int* gpr; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGTRAP ; 
 int THREAD_SIZE ; 
 struct thread_info* current_thread_info () ; 
 int /*<<< orphan*/  kgdb_handle_exception (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pt_regs*) ; 
 int /*<<< orphan*/  memcpy (struct thread_info*,struct thread_info*,int) ; 
 scalar_t__ user_mode (struct pt_regs*) ; 

__attribute__((used)) static int kgdb_singlestep(struct pt_regs *regs)
{
	struct thread_info *thread_info, *exception_thread_info;

	if (user_mode(regs))
		return 0;

	/*
	 * On Book E and perhaps other processsors, singlestep is handled on
	 * the critical exception stack.  This causes current_thread_info()
	 * to fail, since it it locates the thread_info by masking off
	 * the low bits of the current stack pointer.  We work around
	 * this issue by copying the thread_info from the kernel stack
	 * before calling kgdb_handle_exception, and copying it back
	 * afterwards.  On most processors the copy is avoided since
	 * exception_thread_info == thread_info.
	 */
	thread_info = (struct thread_info *)(regs->gpr[1] & ~(THREAD_SIZE-1));
	exception_thread_info = current_thread_info();

	if (thread_info != exception_thread_info)
		memcpy(exception_thread_info, thread_info, sizeof *thread_info);

	kgdb_handle_exception(0, SIGTRAP, 0, regs);

	if (thread_info != exception_thread_info)
		memcpy(thread_info, exception_thread_info, sizeof *thread_info);

	return 1;
}