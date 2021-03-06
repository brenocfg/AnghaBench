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
struct pt_regs {unsigned long ip; unsigned long sp; int flags; int /*<<< orphan*/  ss; int /*<<< orphan*/  cs; } ;

/* Variables and functions */
 int /*<<< orphan*/  USER_DS ; 
 int /*<<< orphan*/  __USER_CS ; 
 int /*<<< orphan*/  __USER_DS ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  ds ; 
 int /*<<< orphan*/  es ; 
 int /*<<< orphan*/  free_thread_xstate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fs ; 
 int /*<<< orphan*/  load_gs_index (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  loadsegment (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  old_rsp ; 
 int /*<<< orphan*/  percpu_write (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  set_fs (int /*<<< orphan*/ ) ; 

void
start_thread(struct pt_regs *regs, unsigned long new_ip, unsigned long new_sp)
{
	loadsegment(fs, 0);
	loadsegment(es, 0);
	loadsegment(ds, 0);
	load_gs_index(0);
	regs->ip		= new_ip;
	regs->sp		= new_sp;
	percpu_write(old_rsp, new_sp);
	regs->cs		= __USER_CS;
	regs->ss		= __USER_DS;
	regs->flags		= 0x200;
	set_fs(USER_DS);
	/*
	 * Free the old FP and other extended state
	 */
	free_thread_xstate(current);
}