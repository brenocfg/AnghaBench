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
 scalar_t__ user_mode (struct pt_regs*) ; 
 int /*<<< orphan*/  xmon_core (struct pt_regs*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xmon_sstep(struct pt_regs *regs)
{
	if (user_mode(regs))
		return 0;
	xmon_core(regs, 0);
	return 1;
}