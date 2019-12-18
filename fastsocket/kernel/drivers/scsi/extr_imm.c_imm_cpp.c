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
 int r_str (unsigned short) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  w_ctr (unsigned short,int) ; 
 int /*<<< orphan*/  w_dtr (unsigned short,int) ; 

__attribute__((used)) static int imm_cpp(unsigned short ppb, unsigned char b)
{
	/*
	 * Comments on udelay values refer to the
	 * Command Packet Protocol (CPP) timing diagram.
	 */

	unsigned char s1, s2, s3;
	w_ctr(ppb, 0x0c);
	udelay(2);		/* 1 usec - infinite */
	w_dtr(ppb, 0xaa);
	udelay(10);		/* 7 usec - infinite */
	w_dtr(ppb, 0x55);
	udelay(10);		/* 7 usec - infinite */
	w_dtr(ppb, 0x00);
	udelay(10);		/* 7 usec - infinite */
	w_dtr(ppb, 0xff);
	udelay(10);		/* 7 usec - infinite */
	s1 = r_str(ppb) & 0xb8;
	w_dtr(ppb, 0x87);
	udelay(10);		/* 7 usec - infinite */
	s2 = r_str(ppb) & 0xb8;
	w_dtr(ppb, 0x78);
	udelay(10);		/* 7 usec - infinite */
	s3 = r_str(ppb) & 0x38;
	/*
	 * Values for b are:
	 * 0000 00aa    Assign address aa to current device
	 * 0010 00aa    Select device aa in EPP Winbond mode
	 * 0010 10aa    Select device aa in EPP mode
	 * 0011 xxxx    Deselect all devices
	 * 0110 00aa    Test device aa
	 * 1101 00aa    Select device aa in ECP mode
	 * 1110 00aa    Select device aa in Compatible mode
	 */
	w_dtr(ppb, b);
	udelay(2);		/* 1 usec - infinite */
	w_ctr(ppb, 0x0c);
	udelay(10);		/* 7 usec - infinite */
	w_ctr(ppb, 0x0d);
	udelay(2);		/* 1 usec - infinite */
	w_ctr(ppb, 0x0c);
	udelay(10);		/* 7 usec - infinite */
	w_dtr(ppb, 0xff);
	udelay(10);		/* 7 usec - infinite */

	/*
	 * The following table is electrical pin values.
	 * (BSY is inverted at the CTR register)
	 *
	 *       BSY  ACK  POut SEL  Fault
	 * S1    0    X    1    1    1
	 * S2    1    X    0    1    1
	 * S3    L    X    1    1    S
	 *
	 * L => Last device in chain
	 * S => Selected
	 *
	 * Observered values for S1,S2,S3 are:
	 * Disconnect => f8/58/78
	 * Connect    => f8/58/70
	 */
	if ((s1 == 0xb8) && (s2 == 0x18) && (s3 == 0x30))
		return 1;	/* Connected */
	if ((s1 == 0xb8) && (s2 == 0x18) && (s3 == 0x38))
		return 0;	/* Disconnected */

	return -1;		/* No device present */
}