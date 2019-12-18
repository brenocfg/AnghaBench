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
struct task_struct {int /*<<< orphan*/  ptrace; } ;

/* Variables and functions */
 int EINVAL ; 
 long PTRACE_O_MASK ; 
 long PTRACE_O_TRACECLONE ; 
 long PTRACE_O_TRACEEXEC ; 
 long PTRACE_O_TRACEEXIT ; 
 long PTRACE_O_TRACEFORK ; 
 long PTRACE_O_TRACESYSGOOD ; 
 long PTRACE_O_TRACEVFORK ; 
 long PTRACE_O_TRACEVFORKDONE ; 
 int /*<<< orphan*/  PT_TRACESYSGOOD ; 
 int /*<<< orphan*/  PT_TRACE_CLONE ; 
 int /*<<< orphan*/  PT_TRACE_EXEC ; 
 int /*<<< orphan*/  PT_TRACE_EXIT ; 
 int /*<<< orphan*/  PT_TRACE_FORK ; 
 int /*<<< orphan*/  PT_TRACE_MASK ; 
 int /*<<< orphan*/  PT_TRACE_VFORK ; 
 int /*<<< orphan*/  PT_TRACE_VFORK_DONE ; 

__attribute__((used)) static int ptrace_setoptions(struct task_struct *child, long data)
{
	child->ptrace &= ~PT_TRACE_MASK;

	if (data & PTRACE_O_TRACESYSGOOD)
		child->ptrace |= PT_TRACESYSGOOD;

	if (data & PTRACE_O_TRACEFORK)
		child->ptrace |= PT_TRACE_FORK;

	if (data & PTRACE_O_TRACEVFORK)
		child->ptrace |= PT_TRACE_VFORK;

	if (data & PTRACE_O_TRACECLONE)
		child->ptrace |= PT_TRACE_CLONE;

	if (data & PTRACE_O_TRACEEXEC)
		child->ptrace |= PT_TRACE_EXEC;

	if (data & PTRACE_O_TRACEVFORKDONE)
		child->ptrace |= PT_TRACE_VFORK_DONE;

	if (data & PTRACE_O_TRACEEXIT)
		child->ptrace |= PT_TRACE_EXIT;

	return (data & ~PTRACE_O_MASK) ? -EINVAL : 0;
}