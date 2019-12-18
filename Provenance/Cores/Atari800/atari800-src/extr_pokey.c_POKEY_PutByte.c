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
 int /*<<< orphan*/  CASSETTE_ResetPOKEY () ; 
 int /*<<< orphan*/  CPU_GenerateIRQ () ; 
 int /*<<< orphan*/  CPU_IRQ ; 
 int /*<<< orphan*/  PBI_IRQ ; 
 int PC ; 
 int /*<<< orphan*/  POKEYSND_Update (int const,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  POKEYSND_UpdateSerio (int,int) ; 
 scalar_t__ POKEYSND_stereo_enabled ; 
 int* POKEY_AUDC ; 
 int* POKEY_AUDCTL ; 
 int* POKEY_AUDF ; 
 int /*<<< orphan*/ * POKEY_Base_mult ; 
 int POKEY_CH1_CH2 ; 
 int POKEY_CH3_CH4 ; 
 size_t POKEY_CHAN1 ; 
 size_t POKEY_CHAN2 ; 
 size_t POKEY_CHAN3 ; 
 size_t POKEY_CHAN4 ; 
 size_t POKEY_CHIP2 ; 
 int POKEY_CLOCK_15 ; 
 int /*<<< orphan*/  POKEY_DELAYED_SERIN_IRQ ; 
 int POKEY_DELAYED_SEROUT_IRQ ; 
 int POKEY_DELAYED_XMTDONE_IRQ ; 
 int /*<<< orphan*/  POKEY_DIV_15 ; 
 int /*<<< orphan*/  POKEY_DIV_64 ; 
 int /*<<< orphan*/ * POKEY_DivNIRQ ; 
 int /*<<< orphan*/ * POKEY_DivNMax ; 
 int POKEY_IRQEN ; 
 int POKEY_IRQST ; 
#define  POKEY_OFFSET_AUDC1 142 
#define  POKEY_OFFSET_AUDC2 141 
#define  POKEY_OFFSET_AUDC3 140 
#define  POKEY_OFFSET_AUDC4 139 
#define  POKEY_OFFSET_AUDCTL 138 
#define  POKEY_OFFSET_AUDF1 137 
#define  POKEY_OFFSET_AUDF2 136 
#define  POKEY_OFFSET_AUDF3 135 
#define  POKEY_OFFSET_AUDF4 134 
#define  POKEY_OFFSET_IRQEN 133 
 int const POKEY_OFFSET_POKEY2 ; 
#define  POKEY_OFFSET_POTGO 132 
#define  POKEY_OFFSET_SEROUT 131 
#define  POKEY_OFFSET_SKCTL 130 
#define  POKEY_OFFSET_SKRES 129 
#define  POKEY_OFFSET_STIMER 128 
 int POKEY_SKCTL ; 
 int POKEY_SKSTAT ; 
 int /*<<< orphan*/  POKEY_siocheck () ; 
 int /*<<< orphan*/  SIO_PutByte (int) ; 
 int SIO_SEROUT_INTERVAL ; 
 int SIO_XMTDONE_INTERVAL ; 
 int /*<<< orphan*/  SOUND_GAIN ; 
 int /*<<< orphan*/  Update_Counter (int) ; 
 int /*<<< orphan*/  VOICEBOX_SEROUTPutByte (int) ; 
 int /*<<< orphan*/  VOICEBOX_SKCTLPutByte (int) ; 
 int pot_scanline ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 

void POKEY_PutByte(UWORD addr, UBYTE byte)
{
#ifdef STEREO_SOUND
	addr &= POKEYSND_stereo_enabled ? 0x1f : 0x0f;
#else
	addr &= 0x0f;
#endif
	switch (addr) {
	case POKEY_OFFSET_AUDC1:
		POKEY_AUDC[POKEY_CHAN1] = byte;
		POKEYSND_Update(POKEY_OFFSET_AUDC1, byte, 0, SOUND_GAIN);
		break;
	case POKEY_OFFSET_AUDC2:
		POKEY_AUDC[POKEY_CHAN2] = byte;
		POKEYSND_Update(POKEY_OFFSET_AUDC2, byte, 0, SOUND_GAIN);
		break;
	case POKEY_OFFSET_AUDC3:
		POKEY_AUDC[POKEY_CHAN3] = byte;
		POKEYSND_Update(POKEY_OFFSET_AUDC3, byte, 0, SOUND_GAIN);
		break;
	case POKEY_OFFSET_AUDC4:
		POKEY_AUDC[POKEY_CHAN4] = byte;
		POKEYSND_Update(POKEY_OFFSET_AUDC4, byte, 0, SOUND_GAIN);
		break;
	case POKEY_OFFSET_AUDCTL:
		POKEY_AUDCTL[0] = byte;

		/* determine the base multiplier for the 'div by n' calculations */
		if (byte & POKEY_CLOCK_15)
			POKEY_Base_mult[0] = POKEY_DIV_15;
		else
			POKEY_Base_mult[0] = POKEY_DIV_64;

		Update_Counter((1 << POKEY_CHAN1) | (1 << POKEY_CHAN2) | (1 << POKEY_CHAN3) | (1 << POKEY_CHAN4));
		POKEYSND_Update(POKEY_OFFSET_AUDCTL, byte, 0, SOUND_GAIN);
		break;
	case POKEY_OFFSET_AUDF1:
		POKEY_AUDF[POKEY_CHAN1] = byte;
		Update_Counter((POKEY_AUDCTL[0] & POKEY_CH1_CH2) ? ((1 << POKEY_CHAN2) | (1 << POKEY_CHAN1)) : (1 << POKEY_CHAN1));
		POKEYSND_Update(POKEY_OFFSET_AUDF1, byte, 0, SOUND_GAIN);
		break;
	case POKEY_OFFSET_AUDF2:
		POKEY_AUDF[POKEY_CHAN2] = byte;
		Update_Counter(1 << POKEY_CHAN2);
		POKEYSND_Update(POKEY_OFFSET_AUDF2, byte, 0, SOUND_GAIN);
		break;
	case POKEY_OFFSET_AUDF3:
		POKEY_AUDF[POKEY_CHAN3] = byte;
		Update_Counter((POKEY_AUDCTL[0] & POKEY_CH3_CH4) ? ((1 << POKEY_CHAN4) | (1 << POKEY_CHAN3)) : (1 << POKEY_CHAN3));
		POKEYSND_Update(POKEY_OFFSET_AUDF3, byte, 0, SOUND_GAIN);
		break;
	case POKEY_OFFSET_AUDF4:
		POKEY_AUDF[POKEY_CHAN4] = byte;
		Update_Counter(1 << POKEY_CHAN4);
		POKEYSND_Update(POKEY_OFFSET_AUDF4, byte, 0, SOUND_GAIN);
		break;
	case POKEY_OFFSET_IRQEN:
		POKEY_IRQEN = byte;
#ifdef DEBUG1
		printf("WR: IRQEN = %x, PC = %x\n", POKEY_IRQEN, PC);
#endif
		POKEY_IRQST |= ~byte & 0xf7;	/* Reset disabled IRQs except XMTDONE */
		if ((~POKEY_IRQST & POKEY_IRQEN) == 0 && PBI_IRQ == 0)
			CPU_IRQ = 0;
		else
			CPU_GenerateIRQ();
		break;
	case POKEY_OFFSET_SKRES:
		POKEY_SKSTAT |= 0xe0;
		break;
	case POKEY_OFFSET_POTGO:
		if (!(POKEY_SKCTL & 4))
			pot_scanline = 0;	/* slow pot mode */
		break;
	case POKEY_OFFSET_SEROUT:
#ifdef VOICEBOX
		VOICEBOX_SEROUTPutByte(byte);
#endif
		if ((POKEY_SKCTL & 0x70) == 0x20 && POKEY_siocheck())
			SIO_PutByte(byte);
		/* check if cassette 2-tone mode has been enabled */
		if ((POKEY_SKCTL & 0x08) == 0x00) {
			/* intelligent device */
			POKEY_DELAYED_SEROUT_IRQ = SIO_SEROUT_INTERVAL;
			POKEY_IRQST |= 0x08;
			POKEY_DELAYED_XMTDONE_IRQ = SIO_XMTDONE_INTERVAL;
		}
		else {
			/* cassette */
			/* some savers patch the cassette baud rate, so we evaluate it here */
			/* scanlines per second*10 bit*audiofrequency/(1.79 MHz/2) */
                        POKEY_DELAYED_SEROUT_IRQ = 312*50*10*(POKEY_AUDF[POKEY_CHAN3] + POKEY_AUDF[POKEY_CHAN4]*0x100)/895000;
			/* safety check */
			if (POKEY_DELAYED_SEROUT_IRQ >= 3) {
                        	POKEY_IRQST |= 0x08;
                        	POKEY_DELAYED_XMTDONE_IRQ = 2*POKEY_DELAYED_SEROUT_IRQ - 2;
			}
			else {
				POKEY_DELAYED_SEROUT_IRQ = 0;
				POKEY_DELAYED_XMTDONE_IRQ = 0;
			}
		};
#ifdef SERIO_SOUND
		POKEYSND_UpdateSerio(1, byte);
#endif
		break;
	case POKEY_OFFSET_STIMER:
		POKEY_DivNIRQ[POKEY_CHAN1] = POKEY_DivNMax[POKEY_CHAN1];
		POKEY_DivNIRQ[POKEY_CHAN2] = POKEY_DivNMax[POKEY_CHAN2];
		POKEY_DivNIRQ[POKEY_CHAN4] = POKEY_DivNMax[POKEY_CHAN4];
		POKEYSND_Update(POKEY_OFFSET_STIMER, byte, 0, SOUND_GAIN);
#ifdef DEBUG1
		printf("WR: STIMER = %x\n", byte);
#endif
		break;
	case POKEY_OFFSET_SKCTL:
#ifdef VOICEBOX
		VOICEBOX_SKCTLPutByte(byte);
#endif
		POKEY_SKCTL = byte;
		POKEYSND_Update(POKEY_OFFSET_SKCTL, byte, 0, SOUND_GAIN);
		if (byte & 4)
			pot_scanline = 228;	/* fast pot mode - return results immediately */
		if ((byte & 0x03) == 0) {
			/* POKEY reset. */
			/* Stop serial IO. */
			POKEY_DELAYED_SERIN_IRQ = 0;
			POKEY_DELAYED_SEROUT_IRQ = 0;
			POKEY_DELAYED_XMTDONE_IRQ = 0;
			CASSETTE_ResetPOKEY();
			/* TODO other registers should also be reset. */
		}
		break;
#ifdef STEREO_SOUND
	case POKEY_OFFSET_AUDC1 + POKEY_OFFSET_POKEY2:
		POKEY_AUDC[POKEY_CHAN1 + POKEY_CHIP2] = byte;
		POKEYSND_Update(POKEY_OFFSET_AUDC1, byte, 1, SOUND_GAIN);
		break;
	case POKEY_OFFSET_AUDC2 + POKEY_OFFSET_POKEY2:
		POKEY_AUDC[POKEY_CHAN2 + POKEY_CHIP2] = byte;
		POKEYSND_Update(POKEY_OFFSET_AUDC2, byte, 1, SOUND_GAIN);
		break;
	case POKEY_OFFSET_AUDC3 + POKEY_OFFSET_POKEY2:
		POKEY_AUDC[POKEY_CHAN3 + POKEY_CHIP2] = byte;
		POKEYSND_Update(POKEY_OFFSET_AUDC3, byte, 1, SOUND_GAIN);
		break;
	case POKEY_OFFSET_AUDC4 + POKEY_OFFSET_POKEY2:
		POKEY_AUDC[POKEY_CHAN4 + POKEY_CHIP2] = byte;
		POKEYSND_Update(POKEY_OFFSET_AUDC4, byte, 1, SOUND_GAIN);
		break;
	case POKEY_OFFSET_AUDCTL + POKEY_OFFSET_POKEY2:
		POKEY_AUDCTL[1] = byte;
		/* determine the base multiplier for the 'div by n' calculations */
		if (byte & POKEY_CLOCK_15)
			POKEY_Base_mult[1] = POKEY_DIV_15;
		else
			POKEY_Base_mult[1] = POKEY_DIV_64;

		POKEYSND_Update(POKEY_OFFSET_AUDCTL, byte, 1, SOUND_GAIN);
		break;
	case POKEY_OFFSET_AUDF1 + POKEY_OFFSET_POKEY2:
		POKEY_AUDF[POKEY_CHAN1 + POKEY_CHIP2] = byte;
		POKEYSND_Update(POKEY_OFFSET_AUDF1, byte, 1, SOUND_GAIN);
		break;
	case POKEY_OFFSET_AUDF2 + POKEY_OFFSET_POKEY2:
		POKEY_AUDF[POKEY_CHAN2 + POKEY_CHIP2] = byte;
		POKEYSND_Update(POKEY_OFFSET_AUDF2, byte, 1, SOUND_GAIN);
		break;
	case POKEY_OFFSET_AUDF3 + POKEY_OFFSET_POKEY2:
		POKEY_AUDF[POKEY_CHAN3 + POKEY_CHIP2] = byte;
		POKEYSND_Update(POKEY_OFFSET_AUDF3, byte, 1, SOUND_GAIN);
		break;
	case POKEY_OFFSET_AUDF4 + POKEY_OFFSET_POKEY2:
		POKEY_AUDF[POKEY_CHAN4 + POKEY_CHIP2] = byte;
		POKEYSND_Update(POKEY_OFFSET_AUDF4, byte, 1, SOUND_GAIN);
		break;
	case POKEY_OFFSET_STIMER + POKEY_OFFSET_POKEY2:
		POKEYSND_Update(POKEY_OFFSET_STIMER, byte, 1, SOUND_GAIN);
		break;
	case POKEY_OFFSET_SKCTL + POKEY_OFFSET_POKEY2:
		POKEYSND_Update(POKEY_OFFSET_SKCTL, byte, 1, SOUND_GAIN);
		break;
#endif
	}
}