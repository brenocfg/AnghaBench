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
typedef  int /*<<< orphan*/  UBYTE ;

/* Variables and functions */
 scalar_t__ Atari800_MACHINE_XLXE ; 
 scalar_t__ Atari800_machine_type ; 
 scalar_t__ FALSE ; 
 int GTIA_GRACTL ; 
 scalar_t__* GTIA_TRIG ; 
 scalar_t__* GTIA_TRIG_latch ; 
 int /*<<< orphan*/  MEMORY_SetRAM (int,int) ; 
 scalar_t__ MEMORY_cartA0BF_enabled ; 
 int /*<<< orphan*/  MEMORY_dFillMem (int,int,int) ; 
 scalar_t__ MEMORY_mem ; 
 int MEMORY_ram_size ; 
 int PIA_PORTB ; 
 int PIA_PORTB_mask ; 
 int /*<<< orphan*/ * builtin_cart (int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  const* under_cartA0BF ; 

void MEMORY_CartA0bfDisable(void)
{
	if (MEMORY_cartA0BF_enabled) {
		/* No BASIC if not XL/XE or bit 1 of PORTB set */
		/* or accessing extended 576K or 1088K memory */
		UBYTE const *builtin = builtin_cart(PIA_PORTB | PIA_PORTB_mask);
		if (builtin == NULL) { /* switch RAM in */
			if (MEMORY_ram_size > 40) {
				memcpy(MEMORY_mem + 0xa000, under_cartA0BF, 0x2000);
				MEMORY_SetRAM(0xa000, 0xbfff);
			}
			else
				MEMORY_dFillMem(0xa000, 0xff, 0x2000);
		}
		else
			memcpy(MEMORY_mem + 0xa000, builtin, 0x2000);
		MEMORY_cartA0BF_enabled = FALSE;
		if (Atari800_machine_type == Atari800_MACHINE_XLXE) {
			GTIA_TRIG[3] = 0;
			if (GTIA_GRACTL & 4)
				GTIA_TRIG_latch[3] = 0;
		}
	}
}