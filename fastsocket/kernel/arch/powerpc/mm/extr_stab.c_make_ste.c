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
struct stab_entry {unsigned long esid_data; unsigned long vsid_data; } ;
struct TYPE_2__ {unsigned long stab_rr; } ;

/* Variables and functions */
 unsigned long ESID_MASK ; 
 unsigned long PAGE_OFFSET ; 
 unsigned long SID_SHIFT ; 
 unsigned long STE_ESID_KP ; 
 unsigned long STE_ESID_KS ; 
 unsigned long STE_ESID_V ; 
 unsigned long STE_VSID_SHIFT ; 
 int /*<<< orphan*/  eieio () ; 
 TYPE_1__* get_paca () ; 

__attribute__((used)) static int make_ste(unsigned long stab, unsigned long esid, unsigned long vsid)
{
	unsigned long esid_data, vsid_data;
	unsigned long entry, group, old_esid, castout_entry, i;
	unsigned int global_entry;
	struct stab_entry *ste, *castout_ste;
	unsigned long kernel_segment = (esid << SID_SHIFT) >= PAGE_OFFSET;

	vsid_data = vsid << STE_VSID_SHIFT;
	esid_data = esid << SID_SHIFT | STE_ESID_KP | STE_ESID_V;
	if (! kernel_segment)
		esid_data |= STE_ESID_KS;

	/* Search the primary group first. */
	global_entry = (esid & 0x1f) << 3;
	ste = (struct stab_entry *)(stab | ((esid & 0x1f) << 7));

	/* Find an empty entry, if one exists. */
	for (group = 0; group < 2; group++) {
		for (entry = 0; entry < 8; entry++, ste++) {
			if (!(ste->esid_data & STE_ESID_V)) {
				ste->vsid_data = vsid_data;
				eieio();
				ste->esid_data = esid_data;
				return (global_entry | entry);
			}
		}
		/* Now search the secondary group. */
		global_entry = ((~esid) & 0x1f) << 3;
		ste = (struct stab_entry *)(stab | (((~esid) & 0x1f) << 7));
	}

	/*
	 * Could not find empty entry, pick one with a round robin selection.
	 * Search all entries in the two groups.
	 */
	castout_entry = get_paca()->stab_rr;
	for (i = 0; i < 16; i++) {
		if (castout_entry < 8) {
			global_entry = (esid & 0x1f) << 3;
			ste = (struct stab_entry *)(stab | ((esid & 0x1f) << 7));
			castout_ste = ste + castout_entry;
		} else {
			global_entry = ((~esid) & 0x1f) << 3;
			ste = (struct stab_entry *)(stab | (((~esid) & 0x1f) << 7));
			castout_ste = ste + (castout_entry - 8);
		}

		/* Dont cast out the first kernel segment */
		if ((castout_ste->esid_data & ESID_MASK) != PAGE_OFFSET)
			break;

		castout_entry = (castout_entry + 1) & 0xf;
	}

	get_paca()->stab_rr = (castout_entry + 1) & 0xf;

	/* Modify the old entry to the new value. */

	/* Force previous translations to complete. DRENG */
	asm volatile("isync" : : : "memory");

	old_esid = castout_ste->esid_data >> SID_SHIFT;
	castout_ste->esid_data = 0;		/* Invalidate old entry */

	asm volatile("sync" : : : "memory");    /* Order update */

	castout_ste->vsid_data = vsid_data;
	eieio();				/* Order update */
	castout_ste->esid_data = esid_data;

	asm volatile("slbie  %0" : : "r" (old_esid << SID_SHIFT));
	/* Ensure completion of slbie */
	asm volatile("sync" : : : "memory");

	return (global_entry | (castout_entry & 0x7));
}