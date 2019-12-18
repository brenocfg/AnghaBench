#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mmu_page_path {int /*<<< orphan*/ ** parent; } ;
struct kvm_mmu_pages {scalar_t__ nr; } ;
struct TYPE_2__ {int level; } ;
struct kvm_mmu_page {TYPE_1__ role; } ;

/* Variables and functions */

__attribute__((used)) static void kvm_mmu_pages_init(struct kvm_mmu_page *parent,
			       struct mmu_page_path *parents,
			       struct kvm_mmu_pages *pvec)
{
	parents->parent[parent->role.level-1] = NULL;
	pvec->nr = 0;
}