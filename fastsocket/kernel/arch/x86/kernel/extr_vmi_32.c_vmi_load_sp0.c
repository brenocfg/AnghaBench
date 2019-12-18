#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ ss1; int /*<<< orphan*/  sp0; } ;
struct tss_struct {TYPE_1__ x86_tss; } ;
struct thread_struct {scalar_t__ sysenter_cs; int /*<<< orphan*/  sp0; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* set_kernel_stack ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_IA32_SYSENTER_CS ; 
 int /*<<< orphan*/  __KERNEL_DS ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 TYPE_2__ vmi_ops ; 
 int /*<<< orphan*/  wrmsr (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vmi_load_sp0(struct tss_struct *tss,
				   struct thread_struct *thread)
{
	tss->x86_tss.sp0 = thread->sp0;

	/* This can only happen when SEP is enabled, no need to test "SEP"arately */
	if (unlikely(tss->x86_tss.ss1 != thread->sysenter_cs)) {
		tss->x86_tss.ss1 = thread->sysenter_cs;
		wrmsr(MSR_IA32_SYSENTER_CS, thread->sysenter_cs, 0);
	}
	vmi_ops.set_kernel_stack(__KERNEL_DS, tss->x86_tss.sp0);
}