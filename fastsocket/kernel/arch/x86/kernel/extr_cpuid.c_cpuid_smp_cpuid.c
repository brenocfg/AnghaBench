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
struct cpuid_regs {int /*<<< orphan*/  edx; int /*<<< orphan*/  ecx; int /*<<< orphan*/  ebx; int /*<<< orphan*/  eax; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpuid_count (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cpuid_smp_cpuid(void *cmd_block)
{
	struct cpuid_regs *cmd = (struct cpuid_regs *)cmd_block;

	cpuid_count(cmd->eax, cmd->ecx,
		    &cmd->eax, &cmd->ebx, &cmd->ecx, &cmd->edx);
}