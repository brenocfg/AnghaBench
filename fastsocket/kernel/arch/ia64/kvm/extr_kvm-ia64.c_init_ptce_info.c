#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * ptce_stride; int /*<<< orphan*/ * ptce_count; int /*<<< orphan*/  ptce_base; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct TYPE_5__ {int /*<<< orphan*/ * stride; int /*<<< orphan*/ * count; int /*<<< orphan*/  base; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ ia64_ptce_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  ia64_get_ptce (TYPE_2__*) ; 

__attribute__((used)) static void init_ptce_info(struct kvm_vcpu *vcpu)
{
	ia64_ptce_info_t ptce = {0};

	ia64_get_ptce(&ptce);
	vcpu->arch.ptce_base = ptce.base;
	vcpu->arch.ptce_count[0] = ptce.count[0];
	vcpu->arch.ptce_count[1] = ptce.count[1];
	vcpu->arch.ptce_stride[0] = ptce.stride[0];
	vcpu->arch.ptce_stride[1] = ptce.stride[1];
}