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

/* Variables and functions */
 unsigned char EndAddr ; 
 int GetBit (int,unsigned char) ; 
 int ReadReg (unsigned int,unsigned char) ; 
 unsigned char StartAddr ; 

__attribute__((used)) static __u8 CheckRegBit(unsigned int BaseAddr, unsigned char RegNum,
		 unsigned char BitPos)
{
	__u8 temp;

	if (BitPos > 7)
		return 0xff;
	if ((RegNum < StartAddr) || (RegNum > EndAddr)) {
//     printf("what is the register %x!\n",RegNum);
	}
	temp = ReadReg(BaseAddr, RegNum);
	return GetBit(temp, BitPos);
}