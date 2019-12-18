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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int MSRPM_ALLOC_ORDER ; 
 int /*<<< orphan*/  MSR_CSTAR ; 
 int /*<<< orphan*/  MSR_FS_BASE ; 
 int /*<<< orphan*/  MSR_GS_BASE ; 
 int /*<<< orphan*/  MSR_IA32_SYSENTER_CS ; 
 int /*<<< orphan*/  MSR_K6_STAR ; 
 int /*<<< orphan*/  MSR_KERNEL_GS_BASE ; 
 int /*<<< orphan*/  MSR_LSTAR ; 
 int /*<<< orphan*/  MSR_SYSCALL_MASK ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  set_msr_interception (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void svm_vcpu_init_msrpm(u32 *msrpm)
{
	memset(msrpm, 0xff, PAGE_SIZE * (1 << MSRPM_ALLOC_ORDER));

#ifdef CONFIG_X86_64
	set_msr_interception(msrpm, MSR_GS_BASE, 1, 1);
	set_msr_interception(msrpm, MSR_FS_BASE, 1, 1);
	set_msr_interception(msrpm, MSR_KERNEL_GS_BASE, 1, 1);
	set_msr_interception(msrpm, MSR_LSTAR, 1, 1);
	set_msr_interception(msrpm, MSR_CSTAR, 1, 1);
	set_msr_interception(msrpm, MSR_SYSCALL_MASK, 1, 1);
#endif
	set_msr_interception(msrpm, MSR_K6_STAR, 1, 1);
	set_msr_interception(msrpm, MSR_IA32_SYSENTER_CS, 1, 1);
}