#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned long debugreg0; unsigned long debugreg1; unsigned long debugreg2; unsigned long debugreg3; unsigned long debugreg6; unsigned long debugreg7; } ;
struct task_struct {TYPE_1__ thread; } ;

/* Variables and functions */

__attribute__((used)) static unsigned long ptrace_get_debugreg(struct task_struct *child, int n)
{
	switch (n) {
	case 0:		return child->thread.debugreg0;
	case 1:		return child->thread.debugreg1;
	case 2:		return child->thread.debugreg2;
	case 3:		return child->thread.debugreg3;
	case 6:		return child->thread.debugreg6;
	case 7:		return child->thread.debugreg7;
	}
	return 0;
}