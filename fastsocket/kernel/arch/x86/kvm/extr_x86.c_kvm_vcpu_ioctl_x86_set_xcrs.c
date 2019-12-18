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
struct kvm_xcrs {int nr_xcrs; TYPE_1__* xcrs; scalar_t__ flags; } ;
struct kvm_vcpu {int dummy; } ;
struct TYPE_2__ {scalar_t__ xcr; int /*<<< orphan*/  value; } ;

/* Variables and functions */
 int EINVAL ; 
 int KVM_MAX_XCRS ; 
 scalar_t__ XCR_XFEATURE_ENABLED_MASK ; 
 int __kvm_set_xcr (struct kvm_vcpu*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_has_xsave ; 

__attribute__((used)) static int kvm_vcpu_ioctl_x86_set_xcrs(struct kvm_vcpu *vcpu,
				       struct kvm_xcrs *guest_xcrs)
{
	int i, r = 0;

	if (!cpu_has_xsave)
		return -EINVAL;

	if (guest_xcrs->nr_xcrs > KVM_MAX_XCRS || guest_xcrs->flags)
		return -EINVAL;

	for (i = 0; i < guest_xcrs->nr_xcrs; i++)
		/* Only support XCR0 currently */
		if (guest_xcrs->xcrs[0].xcr == XCR_XFEATURE_ENABLED_MASK) {
			r = __kvm_set_xcr(vcpu, XCR_XFEATURE_ENABLED_MASK,
				guest_xcrs->xcrs[0].value);
			break;
		}
	if (r)
		r = -EINVAL;
	return r;
}