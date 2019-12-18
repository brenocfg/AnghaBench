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
 int /*<<< orphan*/  kmemcheck_active (struct pt_regs*) ; 
 int /*<<< orphan*/  kmemcheck_hide (struct pt_regs*) ; 

bool kmemcheck_trap(struct pt_regs *regs)
{
	if (!kmemcheck_active(regs))
		return false;

	/* We're done. */
	kmemcheck_hide(regs);
	return true;
}