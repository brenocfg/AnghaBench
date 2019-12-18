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
 int ReadLPCReg (int) ; 
 int ReadReg (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WriteLPCReg (int,int) ; 
 int /*<<< orphan*/  WriteReg (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void SetSITmode(__u16 iobase)
{

	__u8 bTmp;

	bTmp = ReadLPCReg(0x28);
	WriteLPCReg(0x28, bTmp | 0x10);	//select ITMOFF
	bTmp = ReadReg(iobase, 0x35);
	WriteReg(iobase, 0x35, bTmp | 0x40);	// Driver ITMOFF
	WriteReg(iobase, 0x28, bTmp | 0x80);	// enable All interrupt
}