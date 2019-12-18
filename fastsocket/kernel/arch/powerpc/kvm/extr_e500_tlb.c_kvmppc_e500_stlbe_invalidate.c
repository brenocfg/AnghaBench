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
struct tlbe {int /*<<< orphan*/  mas7; int /*<<< orphan*/  mas3; int /*<<< orphan*/  mas2; scalar_t__ mas1; } ;
struct kvmppc_vcpu_e500 {struct tlbe** shadow_tlb; } ;

/* Variables and functions */
 int /*<<< orphan*/  index_of (int,int) ; 
 int /*<<< orphan*/  kvmppc_e500_shadow_release (struct kvmppc_vcpu_e500*,int,int) ; 
 int /*<<< orphan*/  trace_kvm_stlb_inval (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kvmppc_e500_stlbe_invalidate(struct kvmppc_vcpu_e500 *vcpu_e500,
		int tlbsel, int esel)
{
	struct tlbe *stlbe = &vcpu_e500->shadow_tlb[tlbsel][esel];

	kvmppc_e500_shadow_release(vcpu_e500, tlbsel, esel);
	stlbe->mas1 = 0;
	trace_kvm_stlb_inval(index_of(tlbsel, esel), stlbe->mas1, stlbe->mas2,
			     stlbe->mas3, stlbe->mas7);
}