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
struct TYPE_2__ {int tlbsize; } ;

/* Variables and functions */
 unsigned long ASID_MASK ; 
 scalar_t__ CKSEG0 ; 
 int PAGE_SHIFT ; 
 int PARKED_INDEX ; 
 TYPE_1__ current_cpu_data ; 
 int /*<<< orphan*/  ehb () ; 
 int /*<<< orphan*/  mtc0_tlbw_hazard () ; 
 unsigned long read_c0_entryhi () ; 
 int read_c0_wired () ; 
 int /*<<< orphan*/  tlb_read () ; 
 int /*<<< orphan*/  tlb_write_indexed () ; 
 int /*<<< orphan*/  tlbw_use_hazard () ; 
 int /*<<< orphan*/  write_c0_entryhi (scalar_t__) ; 
 int /*<<< orphan*/  write_c0_entrylo0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_c0_entrylo1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_c0_index (int) ; 

void smtc_flush_tlb_asid(unsigned long asid)
{
	int entry;
	unsigned long ehi;

	entry = read_c0_wired();

	/* Traverse all non-wired entries */
	while (entry < current_cpu_data.tlbsize) {
		write_c0_index(entry);
		ehb();
		tlb_read();
		ehb();
		ehi = read_c0_entryhi();
		if ((ehi & ASID_MASK) == asid) {
		    /*
		     * Invalidate only entries with specified ASID,
		     * makiing sure all entries differ.
		     */
		    write_c0_entryhi(CKSEG0 + (entry << (PAGE_SHIFT + 1)));
		    write_c0_entrylo0(0);
		    write_c0_entrylo1(0);
		    mtc0_tlbw_hazard();
		    tlb_write_indexed();
		}
		entry++;
	}
	write_c0_index(PARKED_INDEX);
	tlbw_use_hazard();
}