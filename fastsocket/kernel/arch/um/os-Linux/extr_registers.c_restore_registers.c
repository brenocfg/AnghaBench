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
struct uml_pt_regs {int /*<<< orphan*/  gp; } ;

/* Variables and functions */
 int /*<<< orphan*/  PTRACE_SETREGS ; 
 int errno ; 
 int ptrace (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int restore_registers(int pid, struct uml_pt_regs *regs)
{
	int err;

	err = ptrace(PTRACE_SETREGS, pid, 0, regs->gp);
	if (err < 0)
		return -errno;
	return 0;
}