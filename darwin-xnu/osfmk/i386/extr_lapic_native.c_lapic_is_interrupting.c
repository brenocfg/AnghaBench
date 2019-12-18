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
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IRR_BASE ; 
 int /*<<< orphan*/  ISR_BASE ; 
 int LAPIC_READ_OFFSET (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TRUE ; 

boolean_t
lapic_is_interrupting(uint8_t vector)
{
	int		i;
	int		bit;
	uint32_t	irr;
	uint32_t	isr;

	i = vector / 32;
	bit = 1 << (vector % 32);

	irr = LAPIC_READ_OFFSET(IRR_BASE, i);
	isr = LAPIC_READ_OFFSET(ISR_BASE, i);

	if ((irr | isr) & bit)
		return (TRUE);

	return (FALSE);
}