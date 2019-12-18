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
struct TYPE_2__ {int clocks; int* ToneFreqVals; int* Registers; int* ToneFreqPos; } ;

/* Variables and functions */
 int PSG_CUTOFF ; 
 int PSG_MCYCLES_RATIO ; 
 TYPE_1__ SN76489 ; 
 int /*<<< orphan*/  UpdateToneAmplitude (int,int) ; 

__attribute__((used)) static void RunTone(int i, int clocks)
{
  int time;

  /* Update in case a register changed etc. */
  UpdateToneAmplitude(i, SN76489.clocks);

  /* Time of next transition */
  time = SN76489.ToneFreqVals[i];

  /* Process any transitions that occur within clocks we're running */
  while (time < clocks)
  {
    if (SN76489.Registers[i*2]>PSG_CUTOFF) {
      /* Flip the flip-flop */
      SN76489.ToneFreqPos[i] = -SN76489.ToneFreqPos[i];
    } else {
      /* stuck value */
      SN76489.ToneFreqPos[i] = 1;
    }
    UpdateToneAmplitude(i, time);

    /* Advance to time of next transition */
    time += SN76489.Registers[i*2] * PSG_MCYCLES_RATIO;
  }
  
  /* Update channel tone counter */
  SN76489.ToneFreqVals[i] = time;
}