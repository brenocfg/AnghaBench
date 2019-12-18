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
struct kvm_mmu_page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mmu_page_remove_parent_pte (struct kvm_mmu_page*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void kvm_mmu_put_page(struct kvm_mmu_page *sp, u64 *parent_pte)
{
	mmu_page_remove_parent_pte(sp, parent_pte);
}