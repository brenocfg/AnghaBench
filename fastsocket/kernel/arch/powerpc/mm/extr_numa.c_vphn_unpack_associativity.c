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
typedef  unsigned int u32 ;
typedef  int u16 ;

/* Variables and functions */
 int VPHN_ASSOC_BUFSIZE ; 
 int const VPHN_FIELD_MASK ; 
 int const VPHN_FIELD_MSB ; 
 int const VPHN_FIELD_UNUSED ; 

__attribute__((used)) static int vphn_unpack_associativity(const long *packed, unsigned int *unpacked)
{
	int i, nr_assoc_doms = 0;
	const u16 *field = (const u16*) packed;

#define VPHN_FIELD_UNUSED	(0xffff)
#define VPHN_FIELD_MSB		(0x8000)
#define VPHN_FIELD_MASK		(~VPHN_FIELD_MSB)

	for (i = 0; i < VPHN_ASSOC_BUFSIZE; i++) {
		if (*field == VPHN_FIELD_UNUSED) {
			/* All significant fields processed, and remaining
			 * fields contain the reserved value of all 1's.
			 * Just store them.
			 */
			unpacked[i] = *((u32*)field);
			field += 2;
		} else if (*field & VPHN_FIELD_MSB) {
			/* Data is in the lower 15 bits of this field */
			unpacked[i] = *field & VPHN_FIELD_MASK;
			field++;
			nr_assoc_doms++;
		} else {
			/* Data is in the lower 15 bits of this field
			 * concatenated with the next 16 bit field
			 */
			unpacked[i] = *((u32*)field);
			field += 2;
			nr_assoc_doms++;
		}
	}

	return nr_assoc_doms;
}