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
struct task_struct {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  PT_CCS ; 
 int /*<<< orphan*/  PT_SPC ; 
 unsigned long SBIT_USER ; 
 int /*<<< orphan*/  deconfigure_bp (int /*<<< orphan*/ ) ; 
 unsigned long get_reg (struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_reg (struct task_struct*,int /*<<< orphan*/ ,unsigned long) ; 

void
ptrace_disable(struct task_struct *child)
{
	unsigned long tmp;

	/* Deconfigure SPC and S-bit. */
	tmp = get_reg(child, PT_CCS) & ~SBIT_USER;
	put_reg(child, PT_CCS, tmp);
	put_reg(child, PT_SPC, 0);

	/* Deconfigure any watchpoints associated with the child. */
	deconfigure_bp(child->pid);
}