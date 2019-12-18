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

/* Variables and functions */
 unsigned char EndAddr ; 
 int /*<<< orphan*/  ReadReg (unsigned int,unsigned char) ; 
 int /*<<< orphan*/  ResetBit (int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  SetBit (int /*<<< orphan*/ ,unsigned char) ; 
 unsigned char StartAddr ; 
 int /*<<< orphan*/  WriteReg (unsigned int,unsigned char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int WriteRegBit(unsigned int BaseAddr, unsigned char RegNum,
		unsigned char BitPos, unsigned char value)
{
	__u8 Rtemp, Wtemp;

	if (BitPos > 7) {
		return -1;
	}
	if ((RegNum < StartAddr) || (RegNum > EndAddr))
		return -1;
	Rtemp = ReadReg(BaseAddr, RegNum);
	if (value == 0)
		Wtemp = ResetBit(Rtemp, BitPos);
	else {
		if (value == 1)
			Wtemp = SetBit(Rtemp, BitPos);
		else
			return -1;
	}
	WriteReg(BaseAddr, RegNum, Wtemp);
	return 0;
}