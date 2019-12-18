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
typedef  int /*<<< orphan*/  __u8 ;
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  Rd_Indx (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ResetDongle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetSITmode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Wr_Indx (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  WriteLPCReg (int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void SI_SetMode(__u16 iobase, int mode)
{
	//__u32 dTmp;
	__u8 bTmp;

	WriteLPCReg(0x28, 0x70);	// S/W Reset
	SetSITmode(iobase);
	ResetDongle(iobase);
	udelay(10);
	Wr_Indx(iobase, 0x40, 0x0, 0x17);	//RX ,APEN enable,Normal power
	Wr_Indx(iobase, 0x40, 0x1, mode);	//Set Mode
	Wr_Indx(iobase, 0x40, 0x2, 0xff);	//Set power to FIR VFIR > 1m
	bTmp = Rd_Indx(iobase, 0x40, 1);
}