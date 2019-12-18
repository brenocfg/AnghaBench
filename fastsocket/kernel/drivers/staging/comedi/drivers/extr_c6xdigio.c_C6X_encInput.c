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
struct TYPE_2__ {int sb0; int sb1; int sb2; int sb3; int sb4; int sb5; int sb6; int sb7; } ;
union encvaluetype {int value; TYPE_1__ bits; } ;

/* Variables and functions */
 int C6XDIGIO_TIME_OUT ; 
 int ReadByteFromHwPort (unsigned long) ; 
 int /*<<< orphan*/  WriteByteToHwPort (unsigned long,int) ; 

__attribute__((used)) static int C6X_encInput(unsigned long baseAddr, unsigned channel)
{
	unsigned ppcmd;
	union encvaluetype enc;
	int timeout = 0;
	int tmp;

	/* printk("Inside C6X_encInput\n"); */

	enc.value = 0;
	if (channel == 0) {
		ppcmd = 0x48;
	} else {
		ppcmd = 0x50;
	}
	WriteByteToHwPort(baseAddr, ppcmd);
	tmp = ReadByteFromHwPort(baseAddr + 1);
	while (((tmp & 0x80) == 0) && (timeout < C6XDIGIO_TIME_OUT)) {
		tmp = ReadByteFromHwPort(baseAddr + 1);
		timeout++;
	}

	enc.bits.sb0 = ((ReadByteFromHwPort(baseAddr + 1) >> 3) & 0x7);
	WriteByteToHwPort(baseAddr, ppcmd + 0x4);
	timeout = 0;
	tmp = ReadByteFromHwPort(baseAddr + 1);
	while (((tmp & 0x80) == 0x80) && (timeout < C6XDIGIO_TIME_OUT)) {
		tmp = ReadByteFromHwPort(baseAddr + 1);
		timeout++;
	}
	enc.bits.sb1 = ((ReadByteFromHwPort(baseAddr + 1) >> 3) & 0x7);
	WriteByteToHwPort(baseAddr, ppcmd);
	timeout = 0;
	tmp = ReadByteFromHwPort(baseAddr + 1);
	while (((tmp & 0x80) == 0) && (timeout < C6XDIGIO_TIME_OUT)) {
		tmp = ReadByteFromHwPort(baseAddr + 1);
		timeout++;
	}
	enc.bits.sb2 = ((ReadByteFromHwPort(baseAddr + 1) >> 3) & 0x7);
	WriteByteToHwPort(baseAddr, ppcmd + 0x4);
	timeout = 0;
	tmp = ReadByteFromHwPort(baseAddr + 1);
	while (((tmp & 0x80) == 0x80) && (timeout < C6XDIGIO_TIME_OUT)) {
		tmp = ReadByteFromHwPort(baseAddr + 1);
		timeout++;
	}
	enc.bits.sb3 = ((ReadByteFromHwPort(baseAddr + 1) >> 3) & 0x7);
	WriteByteToHwPort(baseAddr, ppcmd);
	timeout = 0;
	tmp = ReadByteFromHwPort(baseAddr + 1);
	while (((tmp & 0x80) == 0) && (timeout < C6XDIGIO_TIME_OUT)) {
		tmp = ReadByteFromHwPort(baseAddr + 1);
		timeout++;
	}
	enc.bits.sb4 = ((ReadByteFromHwPort(baseAddr + 1) >> 3) & 0x7);
	WriteByteToHwPort(baseAddr, ppcmd + 0x4);
	timeout = 0;
	tmp = ReadByteFromHwPort(baseAddr + 1);
	while (((tmp & 0x80) == 0x80) && (timeout < C6XDIGIO_TIME_OUT)) {
		tmp = ReadByteFromHwPort(baseAddr + 1);
		timeout++;
	}
	enc.bits.sb5 = ((ReadByteFromHwPort(baseAddr + 1) >> 3) & 0x7);
	WriteByteToHwPort(baseAddr, ppcmd);
	timeout = 0;
	tmp = ReadByteFromHwPort(baseAddr + 1);
	while (((tmp & 0x80) == 0x0) && (timeout < C6XDIGIO_TIME_OUT)) {
		tmp = ReadByteFromHwPort(baseAddr + 1);
		timeout++;
	}
	enc.bits.sb6 = ((ReadByteFromHwPort(baseAddr + 1) >> 3) & 0x7);
	WriteByteToHwPort(baseAddr, ppcmd + 0x4);
	timeout = 0;
	tmp = ReadByteFromHwPort(baseAddr + 1);
	while (((tmp & 0x80) == 0x80) && (timeout < C6XDIGIO_TIME_OUT)) {
		tmp = ReadByteFromHwPort(baseAddr + 1);
		timeout++;
	}
	enc.bits.sb7 = ((ReadByteFromHwPort(baseAddr + 1) >> 3) & 0x7);
	WriteByteToHwPort(baseAddr, ppcmd);
	timeout = 0;
	tmp = ReadByteFromHwPort(baseAddr + 1);
	while (((tmp & 0x80) == 0x0) && (timeout < C6XDIGIO_TIME_OUT)) {
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

	return enc.value ^ 0x800000;
}