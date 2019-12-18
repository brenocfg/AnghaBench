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
typedef  int UWORD ;
typedef  int UBYTE ;

/* Variables and functions */
 int /*<<< orphan*/  Atari800_MACHINE_XLXE ; 
 int /*<<< orphan*/  Atari800_machine_type ; 
 int /*<<< orphan*/  INPUT_SelectMultiJoy (int) ; 
 int /*<<< orphan*/  MEMORY_HandlePORTB (int,int) ; 
#define  PIA_OFFSET_PACTL 131 
#define  PIA_OFFSET_PBCTL 130 
#define  PIA_OFFSET_PORTA 129 
#define  PIA_OFFSET_PORTB 128 
 int PIA_PACTL ; 
 int PIA_PBCTL ; 
 int PIA_PORTA ; 
 int PIA_PORTA_mask ; 
 int PIA_PORTB ; 
 int PIA_PORTB_mask ; 
 int /*<<< orphan*/  SIO_SwitchCommandFrame (int) ; 
 int /*<<< orphan*/  SIO_TapeMotor (int) ; 
 int /*<<< orphan*/  XEP80_PutBit (int) ; 
 int /*<<< orphan*/  XEP80_enabled ; 

void PIA_PutByte(UWORD addr, UBYTE byte)
{
	switch (addr & 0x03) {
	case PIA_OFFSET_PACTL:
                /* This code is part of the cassette emulation */
		/* The motor status has changed */
		SIO_TapeMotor(byte & 0x08 ? 0 : 1);
	
		PIA_PACTL = byte;
		break;
	case PIA_OFFSET_PBCTL:
		/* This code is part of the serial I/O emulation */
		if ((PIA_PBCTL ^ byte) & 0x08) {
			/* The command line status has changed */
			SIO_SwitchCommandFrame(byte & 0x08 ? 0 : 1);
		}
		PIA_PBCTL = byte;
		break;
	case PIA_OFFSET_PORTA:
		if ((PIA_PACTL & 0x04) == 0) {
			/* set direction register */
 			PIA_PORTA_mask = ~byte;
		}
		else {
			/* set output register */
#ifdef XEP80_EMULATION
			if (XEP80_enabled && (~PIA_PORTA_mask & 0x11)) {
				XEP80_PutBit(byte);
			}
#endif /* XEP80_EMULATION */
			PIA_PORTA = byte;		/* change from thor */
		}
#ifndef BASIC
		INPUT_SelectMultiJoy((PIA_PORTA | PIA_PORTA_mask) >> 4);
#endif
		break;
	case PIA_OFFSET_PORTB:
		if (Atari800_machine_type == Atari800_MACHINE_XLXE) {
			if ((PIA_PBCTL & 0x04) == 0) {
				/* direction register */
				MEMORY_HandlePORTB((UBYTE) (PIA_PORTB | ~byte), (UBYTE) (PIA_PORTB | PIA_PORTB_mask));
				PIA_PORTB_mask = ~byte;
			}
			else {
				/* output register */
				MEMORY_HandlePORTB((UBYTE) (byte | PIA_PORTB_mask), (UBYTE) (PIA_PORTB | PIA_PORTB_mask));
				PIA_PORTB = byte;
			}
		}
		else {
			if ((PIA_PBCTL & 0x04) == 0) {
				/* direction register */
				PIA_PORTB_mask = ~byte;
			}
			else {
				/* output register */
				PIA_PORTB = byte;
			}
		}
		break;
	}
}