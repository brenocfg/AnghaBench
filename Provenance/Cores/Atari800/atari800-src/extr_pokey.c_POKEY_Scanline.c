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
 scalar_t__ ANTIC_LINE_C ; 
 scalar_t__ CASSETTE_AddScanLine () ; 
 int /*<<< orphan*/  CPU_GenerateIRQ () ; 
 int /*<<< orphan*/  ESC_enable_sio_patch ; 
 int /*<<< orphan*/  INPUT_Scanline () ; 
 int /*<<< orphan*/  POKEYSND_UpdateVolOnly () ; 
 size_t POKEY_CHAN1 ; 
 size_t POKEY_CHAN2 ; 
 size_t POKEY_CHAN4 ; 
 int POKEY_DELAYED_SERIN_IRQ ; 
 scalar_t__ POKEY_DELAYED_SEROUT_IRQ ; 
 scalar_t__ POKEY_DELAYED_XMTDONE_IRQ ; 
 int /*<<< orphan*/ * POKEY_DivNIRQ ; 
 scalar_t__* POKEY_DivNMax ; 
 int POKEY_IRQEN ; 
 int POKEY_IRQST ; 
 int POKEY_SERIN ; 
 int POKEY_SKCTL ; 
 int POKEY_SKSTAT ; 
 int SIO_GetByte () ; 
 int /*<<< orphan*/  pokey_update () ; 
 int pot_scanline ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  random_scanline_counter ; 

void POKEY_Scanline(void)
{
#ifdef POKEY_UPDATE
	pokey_update();
#endif

#ifdef VOL_ONLY_SOUND
	POKEYSND_UpdateVolOnly();
#endif

#ifndef BASIC
	INPUT_Scanline();	/* Handle Amiga and ST mice. */
						/* It's not a part of POKEY emulation, */
						/* but it looks to be the best place to put it. */
#endif

	/* on nonpatched i/o-operation, enable the cassette timing */
	if (!ESC_enable_sio_patch) {
		if (CASSETTE_AddScanLine())
			POKEY_DELAYED_SERIN_IRQ = 1;
	}

	if ((POKEY_SKCTL & 0x03) == 0)
		/* Don't process timers when POKEY is in reset mode. */
		return;

	if (pot_scanline < 228)
		pot_scanline++;

	random_scanline_counter += ANTIC_LINE_C;

	if (POKEY_DELAYED_SERIN_IRQ > 0) {
		if (--POKEY_DELAYED_SERIN_IRQ == 0) {
			/* Load a byte to SERIN - even when the IRQ is disabled. */
			POKEY_SERIN = SIO_GetByte();
			if (POKEY_IRQEN & 0x20) {
				if (POKEY_IRQST & 0x20) {
					POKEY_IRQST &= 0xdf;
#ifdef DEBUG2
					printf("SERIO: SERIN Interrupt triggered, bytevalue %02x\n", POKEY_SERIN);
#endif
				}
				else {
					POKEY_SKSTAT &= 0xdf;
#ifdef DEBUG2
					printf("SERIO: SERIN Interrupt triggered, bytevalue %02x\n", POKEY_SERIN);
#endif
				}
				CPU_GenerateIRQ();
			}
#ifdef DEBUG2
			else {
				printf("SERIO: SERIN Interrupt missed, bytevalue %02x\n", POKEY_SERIN);
			}
#endif
		}
	}

	if (POKEY_DELAYED_SEROUT_IRQ > 0) {
		if (--POKEY_DELAYED_SEROUT_IRQ == 0) {
			if (POKEY_IRQEN & 0x10) {
#ifdef DEBUG2
				printf("SERIO: SEROUT Interrupt triggered\n");
#endif
				POKEY_IRQST &= 0xef;
				CPU_GenerateIRQ();
			}
#ifdef DEBUG2
			else {
				printf("SERIO: SEROUT Interrupt missed\n");
			}
#endif
		}
	}

	if (POKEY_DELAYED_XMTDONE_IRQ > 0)
		if (--POKEY_DELAYED_XMTDONE_IRQ == 0) {
			POKEY_IRQST &= 0xf7;
			if (POKEY_IRQEN & 0x08) {
#ifdef DEBUG2
				printf("SERIO: XMTDONE Interrupt triggered\n");
#endif
				CPU_GenerateIRQ();
			}
#ifdef DEBUG2
			else
				printf("SERIO: XMTDONE Interrupt missed\n");
#endif
		}

	if ((POKEY_DivNIRQ[POKEY_CHAN1] -= ANTIC_LINE_C) < 0 ) {
		POKEY_DivNIRQ[POKEY_CHAN1] += POKEY_DivNMax[POKEY_CHAN1];
		if (POKEY_IRQEN & 0x01) {
			POKEY_IRQST &= 0xfe;
			CPU_GenerateIRQ();
		}
	}

	if ((POKEY_DivNIRQ[POKEY_CHAN2] -= ANTIC_LINE_C) < 0 ) {
		POKEY_DivNIRQ[POKEY_CHAN2] += POKEY_DivNMax[POKEY_CHAN2];
		if (POKEY_IRQEN & 0x02) {
			POKEY_IRQST &= 0xfd;
			CPU_GenerateIRQ();
		}
	}

	if ((POKEY_DivNIRQ[POKEY_CHAN4] -= ANTIC_LINE_C) < 0 ) {
		POKEY_DivNIRQ[POKEY_CHAN4] += POKEY_DivNMax[POKEY_CHAN4];
		if (POKEY_IRQEN & 0x04) {
			POKEY_IRQST &= 0xfb;
			CPU_GenerateIRQ();
		}
	}
}