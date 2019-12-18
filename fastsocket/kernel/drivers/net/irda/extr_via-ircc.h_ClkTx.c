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
 int Clk_bit ; 
 int ReadReg (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Sdelay (int) ; 
 int Tx_bit ; 
 int /*<<< orphan*/  WriteReg (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void ClkTx(__u16 iobase, __u8 Clk, __u8 Tx)
{
	__u8 bTmp;

	bTmp = ReadReg(iobase, 0x34);
	if (Clk == 0)
		bTmp &= ~Clk_bit;
	else {
		if (Clk == 1)
			bTmp |= Clk_bit;
	}
	WriteReg(iobase, 0x34, bTmp);
	Sdelay(1);
	if (Tx == 0)
		bTmp &= ~Tx_bit;
	else {
		if (Tx == 1)
			bTmp |= Tx_bit;
	}
	WriteReg(iobase, 0x34, bTmp);
}