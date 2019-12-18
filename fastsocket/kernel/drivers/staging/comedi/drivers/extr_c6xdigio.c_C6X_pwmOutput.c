#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int sb0; int sb1; int sb2; int sb3; int sb4; } ;
union pwmcmdtype {int cmd; TYPE_1__ bits; } ;

/* Variables and functions */
 int C6XDIGIO_TIME_OUT ; 
 unsigned int ReadByteFromHwPort (unsigned long) ; 
 int /*<<< orphan*/  WriteByteToHwPort (unsigned long,int) ; 

__attribute__((used)) static void C6X_pwmOutput(unsigned long baseAddr, unsigned channel, int value)
{
	unsigned ppcmd;
	union pwmcmdtype pwm;
	int timeout = 0;
	unsigned tmp;

	/* printk("Inside C6X_pwmOutput\n"); */

	pwm.cmd = value;
	if (pwm.cmd > 498)
		pwm.cmd = 498;
	if (pwm.cmd < 2)
		pwm.cmd = 2;

	if (channel == 0) {
		ppcmd = 0x28;
	} else {		/*  if channel == 1 */
		ppcmd = 0x30;
	}			/* endif */

	WriteByteToHwPort(baseAddr, ppcmd + pwm.bits.sb0);
	tmp = ReadByteFromHwPort(baseAddr + 1);
	while (((tmp & 0x80) == 0) && (timeout < C6XDIGIO_TIME_OUT)) {
		tmp = ReadByteFromHwPort(baseAddr + 1);
		timeout++;
	}

	WriteByteToHwPort(baseAddr, ppcmd + pwm.bits.sb1 + 0x4);
	timeout = 0;
	tmp = ReadByteFromHwPort(baseAddr + 1);
	while (((tmp & 0x80) == 0x80) && (timeout < C6XDIGIO_TIME_OUT)) {
		tmp = ReadByteFromHwPort(baseAddr + 1);
		timeout++;
	}

	WriteByteToHwPort(baseAddr, ppcmd + pwm.bits.sb2);
	tmp = ReadByteFromHwPort(baseAddr + 1);
	while (((tmp & 0x80) == 0) && (timeout < C6XDIGIO_TIME_OUT)) {
		tmp = ReadByteFromHwPort(baseAddr + 1);
		timeout++;
	}

	WriteByteToHwPort(baseAddr, ppcmd + pwm.bits.sb3 + 0x4);
	timeout = 0;
	tmp = ReadByteFromHwPort(baseAddr + 1);
	while (((tmp & 0x80) == 0x80) && (timeout < C6XDIGIO_TIME_OUT)) {
		tmp = ReadByteFromHwPort(baseAddr + 1);
		timeout++;
	}

	WriteByteToHwPort(baseAddr, ppcmd + pwm.bits.sb4);
	tmp = ReadByteFromHwPort(baseAddr + 1);
	while (((tmp & 0x80) == 0) && (timeout < C6XDIGIO_TIME_OUT)) {
		tmp = ReadByteFromHwPort(baseAddr + 1);
		timeout++;
	}

	WriteByteToHwPort(baseAddr, 0x0);
	timeout = 0;
	tmp = ReadByteFromHwPort(baseAddr + 1);
	while (((tmp & 0x80) == 0x80) && (timeout < C6XDIGIO_TIME_OUT)) {
		tmp = ReadByteFromHwPort(baseAddr + 1);
		timeout++;
	}

}