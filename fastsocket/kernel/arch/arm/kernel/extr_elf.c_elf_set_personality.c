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
struct elf32_hdr {unsigned int e_flags; } ;

/* Variables and functions */
 unsigned int EF_ARM_APCS_26 ; 
 unsigned int EF_ARM_EABI_MASK ; 
 unsigned int EF_ARM_EABI_UNKNOWN ; 
 unsigned int EF_ARM_SOFT_FLOAT ; 
 int HWCAP_IWMMXT ; 
 unsigned int PER_LINUX ; 
 unsigned int PER_LINUX_32BIT ; 
 int /*<<< orphan*/  TIF_USING_IWMMXT ; 
 int /*<<< orphan*/  clear_thread_flag (int /*<<< orphan*/ ) ; 
 int elf_hwcap ; 
 int /*<<< orphan*/  set_personality (unsigned int) ; 
 int /*<<< orphan*/  set_thread_flag (int /*<<< orphan*/ ) ; 

void elf_set_personality(const struct elf32_hdr *x)
{
	unsigned int eflags = x->e_flags;
	unsigned int personality = PER_LINUX_32BIT;

	/*
	 * APCS-26 is only valid for OABI executables
	 */
	if ((eflags & EF_ARM_EABI_MASK) == EF_ARM_EABI_UNKNOWN) {
		if (eflags & EF_ARM_APCS_26)
			personality = PER_LINUX;
	}

	set_personality(personality);

	/*
	 * Since the FPA coprocessor uses CP1 and CP2, and iWMMXt uses CP0
	 * and CP1, we only enable access to the iWMMXt coprocessor if the
	 * binary is EABI or softfloat (and thus, guaranteed not to use
	 * FPA instructions.)
	 */
	if (elf_hwcap & HWCAP_IWMMXT &&
	    eflags & (EF_ARM_EABI_MASK | EF_ARM_SOFT_FLOAT)) {
		set_thread_flag(TIF_USING_IWMMXT);
	} else {
		clear_thread_flag(TIF_USING_IWMMXT);
	}
}