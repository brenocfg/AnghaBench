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
struct kvm_para_state {int mmu_queue_len; int mmu_queue; } ;

/* Variables and functions */
 scalar_t__ PARAVIRT_LAZY_MMU ; 
 int /*<<< orphan*/  kvm_mmu_op (void*,int) ; 
 struct kvm_para_state* kvm_para_state () ; 
 int /*<<< orphan*/  memcpy (int,void*,int) ; 
 int /*<<< orphan*/  mmu_queue_flush (struct kvm_para_state*) ; 
 scalar_t__ paravirt_get_lazy_mode () ; 

__attribute__((used)) static void kvm_deferred_mmu_op(void *buffer, int len)
{
	struct kvm_para_state *state = kvm_para_state();

	if (paravirt_get_lazy_mode() != PARAVIRT_LAZY_MMU) {
		kvm_mmu_op(buffer, len);
		return;
	}
	if (state->mmu_queue_len + len > sizeof state->mmu_queue)
		mmu_queue_flush(state);
	memcpy(state->mmu_queue + state->mmu_queue_len, buffer, len);
	state->mmu_queue_len += len;
}