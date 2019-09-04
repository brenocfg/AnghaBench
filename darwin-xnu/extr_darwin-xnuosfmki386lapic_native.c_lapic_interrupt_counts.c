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
typedef  int uint64_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRR_BASE ; 
 int /*<<< orphan*/  ISR_BASE ; 
 int LAPIC_READ_OFFSET (int /*<<< orphan*/ ,int) ; 

void
lapic_interrupt_counts(uint64_t intrs[256])
{
	int		i;
	int		j;
	int		bit;
	uint32_t	irr;
	uint32_t	isr;

	if (intrs == NULL)
		return;

	for (i = 0; i < 8; i += 1) {
		irr = LAPIC_READ_OFFSET(IRR_BASE, i);
		isr = LAPIC_READ_OFFSET(ISR_BASE, i);

		if ((isr | irr) == 0)
			continue;

		for (j = (i == 0) ? 16 : 0; j < 32; j += 1) {
			bit = (32 * i) + j;
			if ((isr | irr) & (1 << j))
				intrs[bit] += 1;
		}
	}
}