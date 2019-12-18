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
struct pt_regs {int /*<<< orphan*/  fp; int /*<<< orphan*/  r7; int /*<<< orphan*/  r4; int /*<<< orphan*/  r0; } ;

/* Variables and functions */

__attribute__((used)) static int get_reg(struct pt_regs *regs, int nr)
{
	int val;

	if (nr < 4)
		val = *(unsigned long *)(&regs->r0 + nr);
	else if (nr < 7)
		val = *(unsigned long *)(&regs->r4 + (nr - 4));
	else if (nr < 13)
		val = *(unsigned long *)(&regs->r7 + (nr - 7));
	else
		val = *(unsigned long *)(&regs->fp + (nr - 13));

	return val;
}