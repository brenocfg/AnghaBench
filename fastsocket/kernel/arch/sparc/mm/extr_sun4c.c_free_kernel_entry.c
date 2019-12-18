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
struct sun4c_mmu_ring {int dummy; } ;
struct sun4c_mmu_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_ring (int /*<<< orphan*/ *,struct sun4c_mmu_entry*) ; 
 int /*<<< orphan*/  remove_ring (struct sun4c_mmu_ring*,struct sun4c_mmu_entry*) ; 
 int /*<<< orphan*/  sun4c_kfree_ring ; 

__attribute__((used)) static void free_kernel_entry(struct sun4c_mmu_entry *entry,
			      struct sun4c_mmu_ring *ring)
{
        remove_ring(ring, entry);
        add_ring(&sun4c_kfree_ring, entry);
}