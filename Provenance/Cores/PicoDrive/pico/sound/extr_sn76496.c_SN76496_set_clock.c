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
struct SN76496 {double UpdateStep; double SampleRate; } ;

/* Variables and functions */
 scalar_t__ STEP ; 

__attribute__((used)) static void SN76496_set_clock(struct SN76496 *R,int clock)
{

	/* the base clock for the tone generators is the chip clock divided by 16; */
	/* for the noise generator, it is clock / 256. */
	/* Here we calculate the number of steps which happen during one sample */
	/* at the given sample rate. No. of events = sample rate / (clock/16). */
	/* STEP is a multiplier used to turn the fraction into a fixed point */
	/* number. */
	R->UpdateStep = ((double)STEP * R->SampleRate * 16) / clock;
}