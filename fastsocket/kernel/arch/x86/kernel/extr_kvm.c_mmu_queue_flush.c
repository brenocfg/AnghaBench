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
struct kvm_para_state {scalar_t__ mmu_queue_len; int /*<<< orphan*/  mmu_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvm_mmu_op (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void mmu_queue_flush(struct kvm_para_state *state)
{
	if (state->mmu_queue_len) {
		kvm_mmu_op(state->mmu_queue, state->mmu_queue_len);
		state->mmu_queue_len = 0;
	}
}