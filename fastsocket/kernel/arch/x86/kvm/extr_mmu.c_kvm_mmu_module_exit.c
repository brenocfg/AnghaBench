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

/* Variables and functions */
 int /*<<< orphan*/  kvm_total_used_mmu_pages ; 
 int /*<<< orphan*/  mmu_destroy_caches () ; 
 int /*<<< orphan*/  mmu_shrinker ; 
 int /*<<< orphan*/  percpu_counter_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_shrinker (int /*<<< orphan*/ *) ; 

void kvm_mmu_module_exit(void)
{
	mmu_destroy_caches();
	percpu_counter_destroy(&kvm_total_used_mmu_pages);
	unregister_shrinker(&mmu_shrinker);
}