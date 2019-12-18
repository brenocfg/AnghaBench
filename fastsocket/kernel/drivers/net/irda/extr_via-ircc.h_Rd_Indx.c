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
typedef  int __u8 ;
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  ActClk (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ClkTx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int Rd_Valid ; 
 int ReadReg (int /*<<< orphan*/ ,int) ; 
 int RxBit ; 
 int /*<<< orphan*/  Sdelay (int) ; 
 int /*<<< orphan*/  Tdelay (int) ; 
 int /*<<< orphan*/  Wr_Byte (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static __u8 Rd_Indx(__u16 iobase, __u8 addr, __u8 index)
{
	__u8 data = 0, bTmp, data_bit;
	int i;

	bTmp = addr | (index << 1) | 0;
	ClkTx(iobase, 0, 0);
	Tdelay(2);
	ActClk(iobase, 1);
	udelay(1);
	Wr_Byte(iobase, bTmp);
	Sdelay(1);
	ClkTx(iobase, 0, 0);
	Tdelay(2);
	for (i = 0; i < 10; i++) {
		ActClk(iobase, 1);
		Tdelay(1);
		ActClk(iobase, 0);
		Tdelay(1);
		ClkTx(iobase, 0, 1);
		Tdelay(1);
		bTmp = ReadReg(iobase, 0x34);
		if (!(bTmp & Rd_Valid))
			break;
	}
	if (!(bTmp & Rd_Valid)) {
		for (i = 0; i < 8; i++) {
			ActClk(iobase, 1);
			Tdelay(1);
			ActClk(iobase, 0);
			bTmp = ReadReg(iobase, 0x34);
			data_bit = 1 << i;
			if (bTmp & RxBit)
				data |= data_bit;
			else
				data &= ~data_bit;
			Tdelay(2);
		}
	} else {
		for (i = 0; i < 2; i++) {
			ActClk(iobase, 1);
			Tdelay(1);
			ActClk(iobase, 0);
			Tdelay(2);
		}
		bTmp = ReadReg(iobase, 0x34);
	}
	for (i = 0; i < 1; i++) {
		ActClk(iobase, 1);
		Tdelay(1);
		ActClk(iobase, 0);
		Tdelay(2);
	}
	ClkTx(iobase, 0, 0);
	Tdelay(1);
	for (i = 0; i < 3; i++) {
		ActClk(iobase, 1);
		Tdelay(1);
		ActClk(iobase, 0);
		Tdelay(2);
	}
	return data;
}