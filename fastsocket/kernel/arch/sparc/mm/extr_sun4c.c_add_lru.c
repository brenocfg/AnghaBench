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
struct sun4c_mmu_entry {struct sun4c_mmu_entry* lru_prev; struct sun4c_mmu_entry* lru_next; } ;
struct sun4c_mmu_ring {struct sun4c_mmu_entry ringhd; } ;

/* Variables and functions */
 struct sun4c_mmu_ring sun4c_ulru_ring ; 

__attribute__((used)) static inline void add_lru(struct sun4c_mmu_entry *entry)
{
	struct sun4c_mmu_ring *ring = &sun4c_ulru_ring;
	struct sun4c_mmu_entry *head = &ring->ringhd;

	entry->lru_next = head;
	(entry->lru_prev = head->lru_prev)->lru_next = entry;
	head->lru_prev = entry;
}