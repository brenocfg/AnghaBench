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
 unsigned int APIC_EILVT_MASKED ; 
 int APIC_EILVT_NR_MAX ; 
 unsigned int atomic_cmpxchg (int /*<<< orphan*/ *,unsigned int,unsigned int) ; 
 unsigned int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eilvt_entry_is_changeable (unsigned int,unsigned int) ; 
 int /*<<< orphan*/ * eilvt_offsets ; 

__attribute__((used)) static unsigned int reserve_eilvt_offset(int offset, unsigned int new)
{
	unsigned int rsvd;			/* 0: uninitialized */

	if (offset >= APIC_EILVT_NR_MAX)
		return ~0;

	rsvd = atomic_read(&eilvt_offsets[offset]) & ~APIC_EILVT_MASKED;
	do {
		if (rsvd &&
		    !eilvt_entry_is_changeable(rsvd, new))
			/* may not change if vectors are different */
			return rsvd;
		rsvd = atomic_cmpxchg(&eilvt_offsets[offset], rsvd, new);
	} while (rsvd != new);

	return new;
}