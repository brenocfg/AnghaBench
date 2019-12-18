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
struct sun4c_mmu_entry {unsigned long vaddr; struct sun4c_mmu_entry* next; struct sun4c_mmu_entry* prev; } ;
struct sun4c_mmu_ring {int /*<<< orphan*/  num_entries; struct sun4c_mmu_entry ringhd; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_lru (struct sun4c_mmu_entry*) ; 

__attribute__((used)) static void add_ring_ordered(struct sun4c_mmu_ring *ring,
			     struct sun4c_mmu_entry *entry)
{
	struct sun4c_mmu_entry *head = &ring->ringhd;
	unsigned long addr = entry->vaddr;

	while ((head->next != &ring->ringhd) && (head->next->vaddr < addr))
		head = head->next;

	entry->prev = head;
	(entry->next = head->next)->prev = entry;
	head->next = entry;
	ring->num_entries++;

	add_lru(entry);
}