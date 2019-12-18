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
typedef  int u64 ;
struct TYPE_3__ {int** rsvd_bits_mask; } ;
struct TYPE_4__ {TYPE_1__ mmu; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;

/* Variables and functions */

__attribute__((used)) static bool is_rsvd_bits_set(struct kvm_vcpu *vcpu, u64 gpte, int level)
{
	int bit7;

	bit7 = (gpte >> 7) & 1;
	return (gpte & vcpu->arch.mmu.rsvd_bits_mask[bit7][level-1]) != 0;
}