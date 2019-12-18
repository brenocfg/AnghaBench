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
struct hash_pte {unsigned long v; } ;

/* Variables and functions */
 int /*<<< orphan*/  HPTE_LOCK_BIT ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static inline void native_unlock_hpte(struct hash_pte *hptep)
{
	unsigned long *word = &hptep->v;

	asm volatile("lwsync":::"memory");
	clear_bit(HPTE_LOCK_BIT, word);
}