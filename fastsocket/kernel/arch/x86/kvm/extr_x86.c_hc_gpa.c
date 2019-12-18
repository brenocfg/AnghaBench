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
typedef  unsigned long gpa_t ;

/* Variables and functions */
 scalar_t__ is_long_mode (struct kvm_vcpu*) ; 

__attribute__((used)) static inline gpa_t hc_gpa(struct kvm_vcpu *vcpu, unsigned long a0,
			   unsigned long a1)
{
	if (is_long_mode(vcpu))
		return a0;
	else
		return a0 | ((gpa_t)a1 << 32);
}