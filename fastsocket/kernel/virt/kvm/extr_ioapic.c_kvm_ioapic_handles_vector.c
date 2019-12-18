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
struct kvm_ioapic {int /*<<< orphan*/  handled_vectors; } ;
struct TYPE_2__ {struct kvm_ioapic* vioapic; } ;
struct kvm {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  smp_rmb () ; 
 int test_bit (int,int /*<<< orphan*/ ) ; 

bool kvm_ioapic_handles_vector(struct kvm *kvm, int vector)
{
	struct kvm_ioapic *ioapic = kvm->arch.vioapic;
	smp_rmb();
	return test_bit(vector, ioapic->handled_vectors);
}