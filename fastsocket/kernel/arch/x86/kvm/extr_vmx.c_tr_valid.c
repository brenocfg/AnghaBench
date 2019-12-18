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
struct kvm_segment {int selector; int type; int /*<<< orphan*/  present; scalar_t__ unusable; } ;

/* Variables and functions */
 int SELECTOR_TI_MASK ; 
 int /*<<< orphan*/  VCPU_SREG_TR ; 
 int /*<<< orphan*/  vmx_get_segment (struct kvm_vcpu*,struct kvm_segment*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool tr_valid(struct kvm_vcpu *vcpu)
{
	struct kvm_segment tr;

	vmx_get_segment(vcpu, &tr, VCPU_SREG_TR);

	if (tr.unusable)
		return false;
	if (tr.selector & SELECTOR_TI_MASK)	/* TI = 1 */
		return false;
	if (tr.type != 3 && tr.type != 11) /* TODO: Check if guest is in IA32e mode */
		return false;
	if (!tr.present)
		return false;

	return true;
}