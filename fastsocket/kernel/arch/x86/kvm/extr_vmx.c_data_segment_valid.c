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
struct kvm_vcpu {int dummy; } ;
struct kvm_segment {unsigned int selector; int type; unsigned int dpl; int /*<<< orphan*/  present; int /*<<< orphan*/  s; scalar_t__ unusable; } ;

/* Variables and functions */
 int AR_TYPE_CODE_MASK ; 
 int AR_TYPE_WRITEABLE_MASK ; 
 unsigned int SELECTOR_RPL_MASK ; 
 int /*<<< orphan*/  vmx_get_segment (struct kvm_vcpu*,struct kvm_segment*,int) ; 

__attribute__((used)) static bool data_segment_valid(struct kvm_vcpu *vcpu, int seg)
{
	struct kvm_segment var;
	unsigned int rpl;

	vmx_get_segment(vcpu, &var, seg);
	rpl = var.selector & SELECTOR_RPL_MASK;

	if (var.unusable)
		return true;
	if (!var.s)
		return false;
	if (!var.present)
		return false;
	if (~var.type & (AR_TYPE_CODE_MASK|AR_TYPE_WRITEABLE_MASK)) {
		if (var.dpl < rpl) /* DPL < RPL */
			return false;
	}

	/* TODO: Add other members to kvm_segment_field to allow checking for other access
	 * rights flags
	 */
	return true;
}