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
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 unsigned int PG_LEVEL_4K ; 
 int /*<<< orphan*/ * lookup_address (unsigned long,unsigned int*) ; 
 int /*<<< orphan*/  pte_hidden (int /*<<< orphan*/ ) ; 

pte_t *kmemcheck_pte_lookup(unsigned long address)
{
	pte_t *pte;
	unsigned int level;

	pte = lookup_address(address, &level);
	if (!pte)
		return NULL;
	if (level != PG_LEVEL_4K)
		return NULL;
	if (!pte_hidden(*pte))
		return NULL;

	return pte;
}