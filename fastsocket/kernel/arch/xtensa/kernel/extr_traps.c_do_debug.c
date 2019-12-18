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
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGKILL ; 
 int /*<<< orphan*/  SIGTRAP ; 
 int /*<<< orphan*/  __die_if_kernel (char*,struct pt_regs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  force_sig (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ gdb_enter ; 
 int return_from_debug_flag ; 

void
do_debug(struct pt_regs *regs)
{
#ifdef CONFIG_KGDB
	/* If remote debugging is configured AND enabled, we give control to
	 * kgdb.  Otherwise, we fall through, perhaps giving control to the
	 * native debugger.
	 */

	if (gdb_enter) {
		extern void gdb_handle_exception(struct pt_regs *);
		gdb_handle_exception(regs);
		return_from_debug_flag = 1;
		return;
	}
#endif

	__die_if_kernel("Breakpoint in kernel", regs, SIGKILL);

	/* If in user mode, send SIGTRAP signal to current process */

	force_sig(SIGTRAP, current);
}