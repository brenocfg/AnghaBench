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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int CR4_DE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int get_cr4 () ; 

__attribute__((used)) static boolean_t
dr7d_is_valid(uint32_t *dr7d)
{
	int i;
	uint32_t mask1, mask2;

	/*
	 * If the DE bit is set in CR4, R/W0-3 can be pattern
	 * "10B" to indicate i/o reads and write
	 */
	if (!(get_cr4() & CR4_DE))
		for (i = 0, mask1 = 0x3<<16, mask2 = 0x2<<16; i < 4; 
				i++, mask1 <<= 4, mask2 <<= 4)
			if ((*dr7d & mask1) == mask2)
				return (FALSE);

	/*
	 * if we are doing an instruction execution break (indicated
	 * by r/w[x] being "00B"), then the len[x] must also be set
	 * to "00B"
	 */
	for (i = 0; i < 4; i++)
		if (((((*dr7d >> (16 + i*4))) & 0x3) == 0) &&
				((((*dr7d >> (18 + i*4))) & 0x3) != 0))
			return (FALSE);

	/*
	 * Intel docs have these bits fixed.
	 */
	*dr7d |= 0x1 << 10; /* set bit 10 to 1 */
	*dr7d &= ~(0x1 << 11); /* set bit 11 to 0 */
	*dr7d &= ~(0x1 << 12); /* set bit 12 to 0 */
	*dr7d &= ~(0x1 << 14); /* set bit 14 to 0 */
	*dr7d &= ~(0x1 << 15); /* set bit 15 to 0 */

	/*
	 * We don't allow anything to set the global breakpoints.
	 */

	if (*dr7d & 0x2)
		return (FALSE);

	if (*dr7d & (0x2<<2))
		return (FALSE);

	if (*dr7d & (0x2<<4))
		return (FALSE);

	if (*dr7d & (0x2<<6))
		return (FALSE);

	return (TRUE);
}