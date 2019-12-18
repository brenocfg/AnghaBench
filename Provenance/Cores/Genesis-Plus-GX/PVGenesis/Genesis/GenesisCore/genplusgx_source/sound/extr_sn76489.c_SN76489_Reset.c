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
struct TYPE_2__ {int* Registers; int* ToneFreqPos; int NoiseFreq; scalar_t__ clocks; int /*<<< orphan*/  NoiseShiftRegister; scalar_t__ LatchedRegister; scalar_t__** ChanOut; scalar_t__** Channel; scalar_t__* ToneFreqVals; } ;

/* Variables and functions */
 int /*<<< orphan*/  NoiseInitialState ; 
 TYPE_1__ SN76489 ; 

void SN76489_Reset()
{
  int i;

  for(i = 0; i <= 3; i++)
  {
    /* Initialise PSG state */
    SN76489.Registers[2*i] = 1; /* tone freq=1 */
    SN76489.Registers[2*i+1] = 0xf; /* vol=off */

    /* Set counters to 0 */
    SN76489.ToneFreqVals[i] = 0;

    /* Set flip-flops to 1 */
    SN76489.ToneFreqPos[i] = 1;

    /* Clear stereo channels amplitude */
    SN76489.Channel[i][0] = 0;
    SN76489.Channel[i][1] = 0;

   /* Clear stereo channel outputs in delta buffer */
    SN76489.ChanOut[i][0] = 0;
    SN76489.ChanOut[i][1] = 0;
  }

  /* Initialise latched register index */
  SN76489.LatchedRegister = 0;

  /* Initialise noise generator */
  SN76489.NoiseShiftRegister=NoiseInitialState;
  SN76489.NoiseFreq = 0x10;

  /* Reset internal M-cycle counter */
  SN76489.clocks = 0;
}