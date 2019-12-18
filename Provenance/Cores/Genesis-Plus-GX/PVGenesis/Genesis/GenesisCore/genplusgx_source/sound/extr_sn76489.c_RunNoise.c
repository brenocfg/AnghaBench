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
struct TYPE_2__ {int NoiseFreq; int* Registers; int* ToneFreqVals; int clocks; int* ToneFreqPos; int NoiseShiftRegister; int NoiseFeedback; int SRWidth; } ;

/* Variables and functions */
 int PSG_MCYCLES_RATIO ; 
 TYPE_1__ SN76489 ; 
 int /*<<< orphan*/  UpdateNoiseAmplitude (int) ; 

__attribute__((used)) static void RunNoise(int clocks)
{
  int time;

  /* Noise channel: match to tone2 if in slave mode */
  int NoiseFreq = SN76489.NoiseFreq;
  if (NoiseFreq == 0x80)
  {
    NoiseFreq = SN76489.Registers[2*2];
    SN76489.ToneFreqVals[3] = SN76489.ToneFreqVals[2];
  }

  /* Update in case a register changed etc. */
  UpdateNoiseAmplitude(SN76489.clocks);

  /* Time of next transition */
  time = SN76489.ToneFreqVals[3];

  /* Process any transitions that occur within clocks we're running */
  while (time < clocks)
  {
    /* Flip the flip-flop */
    SN76489.ToneFreqPos[3] = -SN76489.ToneFreqPos[3];
    if (SN76489.ToneFreqPos[3] == 1)
    {
      /* On the positive edge of the square wave (only once per cycle) */
      int Feedback = SN76489.NoiseShiftRegister;
      if ( SN76489.Registers[6] & 0x4 )
      {
        /* White noise */
        /* Calculate parity of fed-back bits for feedback */
        /* Do some optimised calculations for common (known) feedback values */
        /* If two bits fed back, I can do Feedback=(nsr & fb) && (nsr & fb ^ fb) */
        /* since that's (one or more bits set) && (not all bits set) */
        Feedback = ((Feedback & SN76489.NoiseFeedback) && ((Feedback & SN76489.NoiseFeedback) ^ SN76489.NoiseFeedback));
      }
      else    /* Periodic noise */
        Feedback = Feedback & 1;

      SN76489.NoiseShiftRegister = (SN76489.NoiseShiftRegister >> 1) | (Feedback << (SN76489.SRWidth - 1));
      UpdateNoiseAmplitude(time);
    }

    /* Advance to time of next transition */
    time += NoiseFreq * PSG_MCYCLES_RATIO;
  }

  /* Update channel tone counter */
  SN76489.ToneFreqVals[3] = time;
}