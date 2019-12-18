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
struct kvm_para_state {int dummy; } ;

/* Variables and functions */
 struct kvm_para_state* kvm_para_state () ; 
 int /*<<< orphan*/  mmu_queue_flush (struct kvm_para_state*) ; 
 int /*<<< orphan*/  paravirt_leave_lazy_mmu () ; 

__attribute__((used)) static void kvm_leave_lazy_mmu(void)
{
	struct kvm_para_state *state = kvm_para_state();

	mmu_queue_flush(state);
	paravirt_leave_lazy_mmu();
}