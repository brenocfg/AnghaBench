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
 scalar_t__ Atari800_MACHINE_XLXE ; 
 scalar_t__ Atari800_machine_type ; 
 int* GTIA_TRIG ; 
 int /*<<< orphan*/  MEMORY_SetROM (int,int) ; 
 scalar_t__ MEMORY_cartA0BF_enabled ; 
 scalar_t__ MEMORY_mem ; 
 int MEMORY_ram_size ; 
 int PIA_PORTB ; 
 int PIA_PORTB_mask ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/ * builtin_cart (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  under_cartA0BF ; 

void MEMORY_CartA0bfEnable(void)
{
	if (!MEMORY_cartA0BF_enabled) {
		/* No BASIC if not XL/XE or bit 1 of PORTB set */
		/* or accessing extended 576K or 1088K memory */
		if (MEMORY_ram_size > 40 && builtin_cart(PIA_PORTB | PIA_PORTB_mask) == NULL) {
			/* Back-up 0xa000-0xbfff RAM */
			memcpy(under_cartA0BF, MEMORY_mem + 0xa000, 0x2000);
			MEMORY_SetROM(0xa000, 0xbfff);
		}
		MEMORY_cartA0BF_enabled = TRUE;
		if (Atari800_machine_type == Atari800_MACHINE_XLXE)
			GTIA_TRIG[3] = 1;
	}
}