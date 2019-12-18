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
 int /*<<< orphan*/  WriteReg (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void ActClk(__u16 iobase, __u8 value)
{
	__u8 bTmp;
	bTmp = ReadReg(iobase, 0x34);
	if (value)
		WriteReg(iobase, 0x34, bTmp | Clk_bit);
	else
		WriteReg(iobase, 0x34, bTmp & ~Clk_bit);
}