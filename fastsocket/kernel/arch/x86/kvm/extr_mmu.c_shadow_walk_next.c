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
struct kvm_shadow_walk_iterator {int shadow_addr; int* sptep; int /*<<< orphan*/  level; } ;

/* Variables and functions */
 int PT64_BASE_ADDR_MASK ; 

__attribute__((used)) static void shadow_walk_next(struct kvm_shadow_walk_iterator *iterator)
{
	iterator->shadow_addr = *iterator->sptep & PT64_BASE_ADDR_MASK;
	--iterator->level;
}