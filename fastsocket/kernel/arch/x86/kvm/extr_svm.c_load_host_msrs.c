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
struct kvm_vcpu {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  host_gs_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_GS_BASE ; 
 TYPE_1__* to_svm (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  wrmsrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void load_host_msrs(struct kvm_vcpu *vcpu)
{
#ifdef CONFIG_X86_64
	wrmsrl(MSR_GS_BASE, to_svm(vcpu)->host_gs_base);
#endif
}