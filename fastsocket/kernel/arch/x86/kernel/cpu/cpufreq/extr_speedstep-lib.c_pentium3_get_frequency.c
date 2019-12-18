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
typedef  int u8 ;
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_IA32_EBL_CR_POWERON ; 
 unsigned int SPEEDSTEP_CPU_PIII_C_EARLY ; 
 int /*<<< orphan*/  dprintk (char*,...) ; 
 int /*<<< orphan*/  rdmsr (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static unsigned int pentium3_get_frequency(unsigned int processor)
{
	/* See table 14 of p3_ds.pdf and table 22 of 29834003.pdf */
	struct {
		unsigned int ratio;	/* Frequency Multiplier (x10) */
		u8 bitmap;		/* power on configuration bits
					[27, 25:22] (in MSR 0x2a) */
	} msr_decode_mult[] = {
		{ 30, 0x01 },
		{ 35, 0x05 },
		{ 40, 0x02 },
		{ 45, 0x06 },
		{ 50, 0x00 },
		{ 55, 0x04 },
		{ 60, 0x0b },
		{ 65, 0x0f },
		{ 70, 0x09 },
		{ 75, 0x0d },
		{ 80, 0x0a },
		{ 85, 0x26 },
		{ 90, 0x20 },
		{ 100, 0x2b },
		{ 0, 0xff }	/* error or unknown value */
	};

	/* PIII(-M) FSB settings: see table b1-b of 24547206.pdf */
	struct {
		unsigned int value;	/* Front Side Bus speed in MHz */
		u8 bitmap;		/* power on configuration bits [18: 19]
					(in MSR 0x2a) */
	} msr_decode_fsb[] = {
		{  66, 0x0 },
		{ 100, 0x2 },
		{ 133, 0x1 },
		{   0, 0xff}
	};

	u32 msr_lo, msr_tmp;
	int i = 0, j = 0;

	/* read MSR 0x2a - we only need the low 32 bits */
	rdmsr(MSR_IA32_EBL_CR_POWERON, msr_lo, msr_tmp);
	dprintk("P3 - MSR_IA32_EBL_CR_POWERON: 0x%x 0x%x\n", msr_lo, msr_tmp);
	msr_tmp = msr_lo;

	/* decode the FSB */
	msr_tmp &= 0x00c0000;
	msr_tmp >>= 18;
	while (msr_tmp != msr_decode_fsb[i].bitmap) {
		if (msr_decode_fsb[i].bitmap == 0xff)
			return 0;
		i++;
	}

	/* decode the multiplier */
	if (processor == SPEEDSTEP_CPU_PIII_C_EARLY) {
		dprintk("workaround for early PIIIs\n");
		msr_lo &= 0x03c00000;
	} else
		msr_lo &= 0x0bc00000;
	msr_lo >>= 22;
	while (msr_lo != msr_decode_mult[j].bitmap) {
		if (msr_decode_mult[j].bitmap == 0xff)
			return 0;
		j++;
	}

	dprintk("speed is %u\n",
		(msr_decode_mult[j].ratio * msr_decode_fsb[i].value * 100));

	return msr_decode_mult[j].ratio * msr_decode_fsb[i].value * 100;
}