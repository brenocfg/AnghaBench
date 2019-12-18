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
 int read_c0_entryhi () ; 
 unsigned long read_c0_pagemask () ; 
 int /*<<< orphan*/  tlb_write_indexed () ; 
 int /*<<< orphan*/  write_c0_entryhi (unsigned long) ; 
 int /*<<< orphan*/  write_c0_entrylo0 (unsigned long) ; 
 int /*<<< orphan*/  write_c0_entrylo1 (unsigned long) ; 
 int /*<<< orphan*/  write_c0_index (int) ; 
 int /*<<< orphan*/  write_c0_pagemask (unsigned long) ; 

void mod_wired_entry(int entry, unsigned long entrylo0,
		unsigned long entrylo1, unsigned long entryhi,
		unsigned long pagemask)
{
	unsigned long old_pagemask;
	unsigned long old_ctx;

	/* Save old context and create impossible VPN2 value */
	old_ctx = read_c0_entryhi() & 0xff;
	old_pagemask = read_c0_pagemask();
	write_c0_index(entry);
	write_c0_pagemask(pagemask);
	write_c0_entryhi(entryhi);
	write_c0_entrylo0(entrylo0);
	write_c0_entrylo1(entrylo1);
	tlb_write_indexed();
	write_c0_entryhi(old_ctx);
	write_c0_pagemask(old_pagemask);
}