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
struct elf32_hdr {int dummy; } ;

/* Variables and functions */
 scalar_t__ CPU_ARCH_ARMv6 ; 
 int EXSTACK_DISABLE_X ; 
 scalar_t__ cpu_architecture () ; 

int arm_elf_read_implies_exec(const struct elf32_hdr *x, int executable_stack)
{
	if (executable_stack != EXSTACK_DISABLE_X)
		return 1;
	if (cpu_architecture() < CPU_ARCH_ARMv6)
		return 1;
#if !defined(CONFIG_AEABI) || defined(CONFIG_OABI_COMPAT)
	/*
	 * If we have support for OABI programs, we can never allow NX
	 * support - our signal syscall restart mechanism relies upon
	 * being able to execute code placed on the user stack.
	 */
	return 1;
#else
	return 0;
#endif
}