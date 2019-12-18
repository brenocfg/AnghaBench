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
struct TYPE_2__ {int /*<<< orphan*/  id; } ;
struct mm_struct {TYPE_1__ context; } ;

/* Variables and functions */
 int /*<<< orphan*/  MMU_NO_CONTEXT ; 
 int /*<<< orphan*/  __clear_bit (unsigned int,int /*<<< orphan*/ ) ; 
 struct mm_struct** context_mm ; 
 int /*<<< orphan*/  local_flush_tlb_mm (struct mm_struct*) ; 
 int /*<<< orphan*/  pr_hardcont (char*,unsigned int,struct mm_struct*) ; 
 int smp_processor_id () ; 
 int /*<<< orphan*/ * stale_map ; 

__attribute__((used)) static unsigned int steal_context_up(unsigned int id)
{
	struct mm_struct *mm;
	int cpu = smp_processor_id();

	/* Pick up the victim mm */
	mm = context_mm[id];

	pr_hardcont(" | steal %d from 0x%p", id, mm);

	/* Flush the TLB for that context */
	local_flush_tlb_mm(mm);

	/* Mark this mm has having no context anymore */
	mm->context.id = MMU_NO_CONTEXT;

	/* XXX This clear should ultimately be part of local_flush_tlb_mm */
	__clear_bit(id, stale_map[cpu]);

	return id;
}