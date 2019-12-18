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
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  prepare_frametrace (struct pt_regs*) ; 
 int /*<<< orphan*/  show_backtrace (int /*<<< orphan*/ ,struct pt_regs*) ; 

void dump_stack(void)
{
	struct pt_regs regs;

	prepare_frametrace(&regs);
	show_backtrace(current, &regs);
}