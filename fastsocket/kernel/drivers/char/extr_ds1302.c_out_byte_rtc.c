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
 scalar_t__ PLD_RTCCR ; 
 scalar_t__ PLD_RTCRSTODT ; 
 scalar_t__ PLD_RTCWRDATA ; 
 scalar_t__ inw (unsigned long) ; 
 int /*<<< orphan*/  outw (int,unsigned long) ; 

__attribute__((used)) static void
out_byte_rtc(unsigned int reg_addr, unsigned char x)
{
	//RST H
	outw(0x0001,(unsigned long)PLD_RTCRSTODT);
	//write data
	outw(((x<<8)|(reg_addr&0xff)),(unsigned long)PLD_RTCWRDATA);
	//WE
	outw(0x0002,(unsigned long)PLD_RTCCR);
	//wait
	while(inw((unsigned long)PLD_RTCCR));

	//RST L
	outw(0x0000,(unsigned long)PLD_RTCRSTODT);

}