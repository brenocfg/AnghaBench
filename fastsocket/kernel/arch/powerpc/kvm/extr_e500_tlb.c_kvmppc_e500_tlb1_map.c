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
typedef  int /*<<< orphan*/  u64 ;
struct tlbe {int dummy; } ;
struct kvmppc_vcpu_e500 {scalar_t__* guest_tlb_nv; } ;
typedef  int /*<<< orphan*/  gfn_t ;

/* Variables and functions */
 int /*<<< orphan*/  kvmppc_e500_shadow_map (struct kvmppc_vcpu_e500*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tlbe*,int,unsigned int) ; 
 scalar_t__ tlb1_max_shadow_size () ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int kvmppc_e500_tlb1_map(struct kvmppc_vcpu_e500 *vcpu_e500,
		u64 gvaddr, gfn_t gfn, struct tlbe *gtlbe)
{
	unsigned int victim;

	victim = vcpu_e500->guest_tlb_nv[1]++;

	if (unlikely(vcpu_e500->guest_tlb_nv[1] >= tlb1_max_shadow_size()))
		vcpu_e500->guest_tlb_nv[1] = 0;

	kvmppc_e500_shadow_map(vcpu_e500, gvaddr, gfn, gtlbe, 1, victim);

	return victim;
}