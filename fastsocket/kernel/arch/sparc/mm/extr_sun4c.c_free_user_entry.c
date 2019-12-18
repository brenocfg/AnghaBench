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
struct sun4c_mmu_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_ring (int /*<<< orphan*/ *,struct sun4c_mmu_entry*) ; 
 int /*<<< orphan*/  remove_lru (struct sun4c_mmu_entry*) ; 
 int /*<<< orphan*/  remove_ring (scalar_t__,struct sun4c_mmu_entry*) ; 
 scalar_t__ sun4c_context_ring ; 
 int /*<<< orphan*/  sun4c_ufree_ring ; 

__attribute__((used)) static void free_user_entry(int ctx, struct sun4c_mmu_entry *entry)
{
        remove_ring(sun4c_context_ring+ctx, entry);
	remove_lru(entry);
        add_ring(&sun4c_ufree_ring, entry);
}