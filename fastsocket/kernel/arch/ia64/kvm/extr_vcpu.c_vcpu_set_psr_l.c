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

/* Variables and functions */
 unsigned long MASK (int,int) ; 
 unsigned long vcpu_get_psr (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vcpu_set_psr (struct kvm_vcpu*,unsigned long) ; 

void vcpu_set_psr_l(struct kvm_vcpu *vcpu, unsigned long val)
{
	val = (val & MASK(0, 32)) | (vcpu_get_psr(vcpu) & MASK(32, 32));
	vcpu_set_psr(vcpu, val);
}