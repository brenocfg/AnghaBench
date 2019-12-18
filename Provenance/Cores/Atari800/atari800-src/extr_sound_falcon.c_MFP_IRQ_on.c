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
 int* DMActrlptr ; 
 int IVECTOR ; 
 int /*<<< orphan*/  Jenabint (int) ; 
 int /*<<< orphan*/  Mfpint (int,int /*<<< orphan*/ ) ; 
 scalar_t__ RATE25KHZ ; 
 scalar_t__ RATE50KHZ ; 
 int /*<<< orphan*/  Setbuffer (long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Xbtimer (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dsp_buffer1 ; 
 scalar_t__ dsprate ; 
 int /*<<< orphan*/  sndbufsize ; 
 int /*<<< orphan*/  timer_A ; 

void MFP_IRQ_on(void)
{
	Setbuffer((long)dsp_buffer1, sndbufsize);		/* start playing first buffer */
	if (dsprate == RATE25KHZ)
		DMActrlptr[0x10] = 0x80 | 2;	/* mono 25 kHz */
	else if (dsprate == RATE50KHZ)
		DMActrlptr[0x10] = 0x80 | 3;	/* mono 50 kHz */
	else
		DMActrlptr[0x10] = 0x80 | 1;	/* mono 12 kHz */

	DMActrlptr[0] = 0x400 | 3;	/* play until stopped, interrupt at end of frame */

	Mfpint(13, timer_A);
	Xbtimer(0, 8, 1, timer_A);	/* event count mode, interrupt after 1st frame */
	IVECTOR &= ~(1 << 3);		/* turn on AEO */
	Jenabint(13);
}