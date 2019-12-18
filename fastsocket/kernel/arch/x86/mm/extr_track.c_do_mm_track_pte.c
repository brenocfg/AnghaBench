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
typedef  int /*<<< orphan*/  pte_t ;
struct TYPE_2__ {unsigned long bitcnt; int /*<<< orphan*/  count; int /*<<< orphan*/  vector; } ;

/* Variables and functions */
 int _PAGE_DIRTY ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 TYPE_1__ mm_tracking_struct ; 
 unsigned long pte_pfn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_present (int /*<<< orphan*/ ) ; 
 int pte_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_and_set_bit (unsigned long,int /*<<< orphan*/ ) ; 

void do_mm_track_pte(void *val)
{
	pte_t *ptep = (pte_t *)val;
	unsigned long pfn;

	if (!pte_present(*ptep))
		return;

	if (!(pte_val(*ptep) & _PAGE_DIRTY))
		return;

	pfn = pte_pfn(*ptep);

	if (pfn >= mm_tracking_struct.bitcnt)
		return;

	if (!test_and_set_bit(pfn, mm_tracking_struct.vector))
		atomic_inc(&mm_tracking_struct.count);
}