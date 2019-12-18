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
 int /*<<< orphan*/  MEMORY_HandlePORTB (int,int /*<<< orphan*/ ) ; 
 int PIA_PORTA ; 
 int PIA_PORTB ; 
 int PIA_PORTB_mask ; 

void PIA_Reset(void)
{
	PIA_PORTA = 0xff;
	if (Atari800_machine_type == Atari800_MACHINE_XLXE) {
		MEMORY_HandlePORTB(0xff, (UBYTE) (PIA_PORTB | PIA_PORTB_mask));
	}
	PIA_PORTB = 0xff;
}