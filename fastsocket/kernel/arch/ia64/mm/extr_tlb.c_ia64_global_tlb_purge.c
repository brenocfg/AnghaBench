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
struct mm_struct {int dummy; } ;
struct TYPE_2__ {struct mm_struct* active_mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  activate_context (struct mm_struct*) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  down_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_tlb_all () ; 
 int /*<<< orphan*/  ia64_ptcga (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  ia64_srlz_i () ; 
 scalar_t__ need_ptcg_sem ; 
 int /*<<< orphan*/  ptcg_sem ; 
 int toolatetochangeptcgsem ; 
 int /*<<< orphan*/  up_spin (int /*<<< orphan*/ *) ; 

void
ia64_global_tlb_purge (struct mm_struct *mm, unsigned long start,
		       unsigned long end, unsigned long nbits)
{
	struct mm_struct *active_mm = current->active_mm;

	toolatetochangeptcgsem = 1;

	if (mm != active_mm) {
		/* Restore region IDs for mm */
		if (mm && active_mm) {
			activate_context(mm);
		} else {
			flush_tlb_all();
			return;
		}
	}

	if (need_ptcg_sem)
		down_spin(&ptcg_sem);

	do {
		/*
		 * Flush ALAT entries also.
		 */
		ia64_ptcga(start, (nbits << 2));
		ia64_srlz_i();
		start += (1UL << nbits);
	} while (start < end);

	if (need_ptcg_sem)
		up_spin(&ptcg_sem);

        if (mm != active_mm) {
                activate_context(active_mm);
        }
}