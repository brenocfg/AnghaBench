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
 int /*<<< orphan*/  I_CF_H_1 ; 
 int /*<<< orphan*/  I_CF_L_1 ; 
 int ReadReg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WriteReg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void SetPulseWidth(__u16 iobase, __u8 width)
{
	__u8 temp, temp1, temp2;

	temp = (ReadReg(iobase, I_CF_L_1) & 0x1f);
	temp1 = (ReadReg(iobase, I_CF_H_1) & 0xfc);
	temp2 = (width & 0x07) << 5;
	temp |= temp2;
	temp2 = (width & 0x18) >> 3;
	temp1 |= temp2;
	WriteReg(iobase, I_CF_L_1, temp);
	WriteReg(iobase, I_CF_H_1, temp1);
}