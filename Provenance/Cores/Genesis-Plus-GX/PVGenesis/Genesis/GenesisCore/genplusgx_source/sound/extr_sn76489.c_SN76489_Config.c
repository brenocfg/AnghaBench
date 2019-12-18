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
struct TYPE_2__ {unsigned int clocks; int** PreAmp; int** Channel; size_t* Registers; } ;

/* Variables and functions */
 int* PSGVolumeValues ; 
 unsigned int PSG_MCYCLES_RATIO ; 
 TYPE_1__ SN76489 ; 
 int /*<<< orphan*/  SN76489_RunUntil (unsigned int) ; 

void SN76489_Config(unsigned int clocks, int preAmp, int boostNoise, int stereo)
{
  int i;

  /* cycle-accurate Game Gear stereo */
  if (clocks > SN76489.clocks)
  {
    /* Run chip until current timestamp */
    SN76489_RunUntil(clocks);

    /* Update internal M-cycle counter */
    SN76489.clocks += ((clocks - SN76489.clocks + PSG_MCYCLES_RATIO - 1) / PSG_MCYCLES_RATIO) * PSG_MCYCLES_RATIO;
  }

  for (i=0; i<4; i++)
  {
    /* stereo channel pre-amplification */
    SN76489.PreAmp[i][0] = preAmp * ((stereo >> (i + 4)) & 1);
    SN76489.PreAmp[i][1] = preAmp * ((stereo >> (i + 0)) & 1);

    /* noise channel boost */
    if (i == 3)
    {
      SN76489.PreAmp[3][0] = SN76489.PreAmp[3][0] << boostNoise;
      SN76489.PreAmp[3][1] = SN76489.PreAmp[3][1] << boostNoise;
    }

    /* update stereo channel amplitude */
    SN76489.Channel[i][0]= (PSGVolumeValues[SN76489.Registers[i*2 + 1]] * SN76489.PreAmp[i][0]) / 100;
    SN76489.Channel[i][1]= (PSGVolumeValues[SN76489.Registers[i*2 + 1]] * SN76489.PreAmp[i][1]) / 100;
  }
}