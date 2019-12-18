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
 int /*<<< orphan*/  __load_new_mm_context (struct mm_struct*) ; 
 int /*<<< orphan*/  asn_locked () ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  flush_tlb_other (struct mm_struct*) ; 

__attribute__((used)) static void
ipi_flush_icache_page(void *x)
{
	struct mm_struct *mm = (struct mm_struct *) x;
	if (mm == current->active_mm && !asn_locked())
		__load_new_mm_context(mm);
	else
		flush_tlb_other(mm);
}