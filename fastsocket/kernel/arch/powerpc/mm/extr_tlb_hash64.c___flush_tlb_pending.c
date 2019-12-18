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
struct ppc64_tlb_batch {int index; int /*<<< orphan*/  ssize; int /*<<< orphan*/  psize; int /*<<< orphan*/ * pte; int /*<<< orphan*/ * vaddr; int /*<<< orphan*/  mm; } ;
struct cpumask {int dummy; } ;

/* Variables and functions */
 scalar_t__ cpumask_equal (int /*<<< orphan*/ ,struct cpumask const*) ; 
 struct cpumask* cpumask_of (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_hash_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  flush_hash_range (int,int) ; 
 int /*<<< orphan*/  mm_cpumask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_processor_id () ; 

void __flush_tlb_pending(struct ppc64_tlb_batch *batch)
{
	const struct cpumask *tmp;
	int i, local = 0;

	i = batch->index;
	tmp = cpumask_of(smp_processor_id());
	if (cpumask_equal(mm_cpumask(batch->mm), tmp))
		local = 1;
	if (i == 1)
		flush_hash_page(batch->vaddr[0], batch->pte[0],
				batch->psize, batch->ssize, local);
	else
		flush_hash_range(i, local);
	batch->index = 0;
}