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
struct kvm_xcrs {int nr_xcrs; TYPE_2__* xcrs; scalar_t__ flags; } ;
struct TYPE_3__ {int /*<<< orphan*/  xcr0; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct TYPE_4__ {int /*<<< orphan*/  value; int /*<<< orphan*/  xcr; } ;

/* Variables and functions */
 int /*<<< orphan*/  XCR_XFEATURE_ENABLED_MASK ; 
 int /*<<< orphan*/  cpu_has_xsave ; 

__attribute__((used)) static void kvm_vcpu_ioctl_x86_get_xcrs(struct kvm_vcpu *vcpu,
					struct kvm_xcrs *guest_xcrs)
{
	if (!cpu_has_xsave) {
		guest_xcrs->nr_xcrs = 0;
		return;
	}

	guest_xcrs->nr_xcrs = 1;
	guest_xcrs->flags = 0;
	guest_xcrs->xcrs[0].xcr = XCR_XFEATURE_ENABLED_MASK;
	guest_xcrs->xcrs[0].value = vcpu->arch.xcr0;
}