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
 int /*<<< orphan*/  CPU_GenerateIRQ () ; 
 scalar_t__ CommandIndex ; 
 int /*<<< orphan*/  D (int /*<<< orphan*/ ) ; 
 scalar_t__ DataIndex ; 
 int ExpectedBytes ; 
 int /*<<< orphan*/  PBI_IRQ ; 
 int /*<<< orphan*/  PBI_XLD_votrax_busy_callback (int /*<<< orphan*/ ) ; 
 scalar_t__ PIO_CommandFrame ; 
 int /*<<< orphan*/  PIO_PutByte (int) ; 
 scalar_t__ PIO_ReadFrame ; 
 scalar_t__ PIO_StatusRead ; 
 int /*<<< orphan*/  POKEY_IRQEN ; 
 int /*<<< orphan*/  POKEY_OFFSET_IRQEN ; 
 int /*<<< orphan*/  POKEY_PutByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ TransferStatus ; 
 int /*<<< orphan*/  VOICE_MASK ; 
 int /*<<< orphan*/  VOTRAXSND_PutByte (int) ; 
 scalar_t__ VOTRAXSND_busy ; 
 int /*<<< orphan*/  Votrax_GetStatus () ; 
 int modem_latch ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int votrax_latch ; 
 scalar_t__ xld_d_enabled ; 

void PBI_XLD_D1PutByte(UWORD addr, UBYTE byte)
{
	if ((addr & ~3) == 0xd104)  {
		/* XLD disk strobe line */
		D(printf("votrax write:%4x\n",addr));
		if (VOTRAXSND_busy) {
			PBI_XLD_votrax_busy_callback(TRUE); /* idle -> busy */
		}
		VOTRAXSND_PutByte(votrax_latch & 0x3f);

	}
	else if ((addr & ~3) == 0xd100 )  {
		/* votrax phoneme+irq-enable latch */
		if ( !(votrax_latch & 0x80) && (byte & 0x80) && (!Votrax_GetStatus())) {
			/* IRQ disabled -> enabled, and votrax idle: generate IRQ */
			D(printf("votrax IRQ generated: IRQ enable changed and idle\n"));
			CPU_GenerateIRQ();
			PBI_IRQ |= VOICE_MASK;
		} else if ((votrax_latch & 0x80) && !(byte & 0x80) ){
			/* IRQ enabled -> disabled : stop IRQ */
			PBI_IRQ &= ~VOICE_MASK;
			/* update pokey IRQ status */
			POKEY_PutByte(POKEY_OFFSET_IRQEN, POKEY_IRQEN);
		}
		votrax_latch = byte;
	}
	else if (addr == 0xd108) {
	/* modem latch and XLD 8040 T1 input */
		D(printf("XLD 8040 T1:%d loop-back:%d modem+phone:%d offhook(modem relay):%d phaudio:%d DTMF:%d O/!A(originate/answer):%d SQT(squelch transmitter):%d\n",!!(byte&0x80),!!(byte&0x40),!!(byte&0x20),!!(byte&0x10),!!(byte&0x08),!!(byte&0x04),!!(byte&0x02),!!(byte&0x01)));
		modem_latch = byte;
	}
	else if (xld_d_enabled && addr == 0xd110) {
	/* XLD byte output from atari to disk latch */ 
		D(printf("d110: disk output byte:%2x\n",byte));
		if (modem_latch & 0x80){
			/* 8040 T1=1 */
			CommandIndex = 0;
			DataIndex = 0;
			TransferStatus = PIO_CommandFrame;
			ExpectedBytes = 5;
			D(printf("command frame expected\n"));
		}
		else if (TransferStatus == PIO_StatusRead || TransferStatus == PIO_ReadFrame) {
			D(printf("read ack strobe\n"));
		}
		else {
			PIO_PutByte(byte);
		}
	}
}