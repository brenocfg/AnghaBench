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

/* Variables and functions */
 int /*<<< orphan*/  PGD_TABLE_SIZE ; 
 int /*<<< orphan*/  PMD_TABLE_SIZE ; 
 int /*<<< orphan*/  SLAB_PANIC ; 
 int /*<<< orphan*/  kmem_cache_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgd_ctor ; 
 int /*<<< orphan*/ * pgtable_cache ; 
 int /*<<< orphan*/ * pgtable_cache_name ; 
 int /*<<< orphan*/  pmd_ctor ; 

void pgtable_cache_init(void)
{
	pgtable_cache[0] = kmem_cache_create(pgtable_cache_name[0], PGD_TABLE_SIZE, PGD_TABLE_SIZE, SLAB_PANIC, pgd_ctor);
	pgtable_cache[1] = kmem_cache_create(pgtable_cache_name[1], PMD_TABLE_SIZE, PMD_TABLE_SIZE, SLAB_PANIC, pmd_ctor);
}