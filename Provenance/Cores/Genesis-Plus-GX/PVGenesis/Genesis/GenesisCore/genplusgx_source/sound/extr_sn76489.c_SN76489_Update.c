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
struct TYPE_2__ {unsigned int clocks; unsigned int* ToneFreqVals; } ;

/* Variables and functions */
 unsigned int PSG_MCYCLES_RATIO ; 
 TYPE_1__ SN76489 ; 
 int /*<<< orphan*/  SN76489_RunUntil (unsigned int) ; 

void SN76489_Update(unsigned int clocks)
{
  int i;

  if (clocks > SN76489.clocks)
  {
    /* Run chip until current timestamp */
    SN76489_RunUntil(clocks);

    /* Update internal M-cycle counter */
    SN76489.clocks += ((clocks - SN76489.clocks + PSG_MCYCLES_RATIO - 1) / PSG_MCYCLES_RATIO) * PSG_MCYCLES_RATIO;
  }

  /* Adjust internal M-cycle counter for next frame */
  SN76489.clocks -= clocks;

	/* Adjust channel time counters for new frame */
	for (i=0; i<4; ++i)
	{
		SN76489.ToneFreqVals[i] -= clocks;
	}
}