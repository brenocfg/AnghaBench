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
struct sun4c_mmu_entry {TYPE_1__* lru_prev; struct sun4c_mmu_entry* lru_next; } ;
struct TYPE_2__ {struct sun4c_mmu_entry* lru_next; } ;

/* Variables and functions */

__attribute__((used)) static void remove_lru(struct sun4c_mmu_entry *entry)
{
	struct sun4c_mmu_entry *next = entry->lru_next;

	(next->lru_prev = entry->lru_prev)->lru_next = next;
}