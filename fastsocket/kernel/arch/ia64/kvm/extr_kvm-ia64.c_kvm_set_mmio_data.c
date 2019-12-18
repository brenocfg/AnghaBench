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
struct kvm_vcpu {int /*<<< orphan*/  mmio_data; int /*<<< orphan*/  mmio_is_write; } ;
struct kvm_mmio_req {int /*<<< orphan*/  state; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  STATE_IORESP_READY ; 
 struct kvm_mmio_req* kvm_get_vcpu_ioreq (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void kvm_set_mmio_data(struct kvm_vcpu *vcpu)
{
	struct kvm_mmio_req *p = kvm_get_vcpu_ioreq(vcpu);

	if (!vcpu->mmio_is_write)
		memcpy(&p->data, vcpu->mmio_data, 8);
	p->state = STATE_IORESP_READY;
}