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
struct kvmppc_vcpu_44x {int* shadow_tlb_mod; } ;

/* Variables and functions */

__attribute__((used)) static void kvmppc_44x_tlbe_set_modified(struct kvmppc_vcpu_44x *vcpu_44x,
                                         unsigned int i)
{
	vcpu_44x->shadow_tlb_mod[i] = 1;
}