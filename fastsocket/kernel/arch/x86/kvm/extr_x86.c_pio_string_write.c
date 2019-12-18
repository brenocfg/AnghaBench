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
struct kvm_pio_request {int cur_count; int /*<<< orphan*/  size; int /*<<< orphan*/  port; } ;
struct TYPE_2__ {void* pio_data; struct kvm_pio_request pio; } ;
struct kvm_vcpu {int /*<<< orphan*/  kvm; TYPE_1__ arch; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  KVM_PIO_BUS ; 
 scalar_t__ kvm_io_bus_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int pio_string_write(struct kvm_vcpu *vcpu)
{
	struct kvm_pio_request *io = &vcpu->arch.pio;
	void *pd = vcpu->arch.pio_data;
	int i, r = 0;

	for (i = 0; i < io->cur_count; i++) {
		if (kvm_io_bus_write(vcpu->kvm, KVM_PIO_BUS,
				     io->port, io->size, pd)) {
			r = -EOPNOTSUPP;
			break;
		}
		pd += io->size;
	}
	return r;
}