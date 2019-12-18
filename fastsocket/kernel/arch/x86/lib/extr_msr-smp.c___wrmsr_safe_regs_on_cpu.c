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
struct msr_regs_info {int /*<<< orphan*/  regs; int /*<<< orphan*/  err; } ;

/* Variables and functions */
 int /*<<< orphan*/  wrmsr_safe_regs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __wrmsr_safe_regs_on_cpu(void *info)
{
	struct msr_regs_info *rv = info;

	rv->err = wrmsr_safe_regs(rv->regs);
}