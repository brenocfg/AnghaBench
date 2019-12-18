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
 scalar_t__ ia64_get_pkr (unsigned long) ; 

unsigned long vcpu_get_pkr(struct kvm_vcpu *vcpu, unsigned long reg)
{
	return ((unsigned long)ia64_get_pkr(reg));
}