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
struct TYPE_2__ {unsigned int clocks; unsigned int LatchedRegister; int* Registers; unsigned int** Channel; unsigned int** PreAmp; int NoiseFreq; int /*<<< orphan*/  NoiseShiftRegister; } ;

/* Variables and functions */
 int /*<<< orphan*/  NoiseInitialState ; 
 unsigned int* PSGVolumeValues ; 
 unsigned int PSG_MCYCLES_RATIO ; 
 TYPE_1__ SN76489 ; 
 int /*<<< orphan*/  SN76489_RunUntil (unsigned int) ; 

void SN76489_Write(unsigned int clocks, unsigned int data)
{
  unsigned int index;

  if (clocks > SN76489.clocks)
  {
    /* run chip until current timestamp */
    SN76489_RunUntil(clocks);

    /* update internal M-cycle counter */
    SN76489.clocks += ((clocks - SN76489.clocks + PSG_MCYCLES_RATIO - 1) / PSG_MCYCLES_RATIO) * PSG_MCYCLES_RATIO;
  }

  if (data & 0x80)
  {
    /* latch byte  %1 cc t dddd */
    SN76489.LatchedRegister = index = (data >> 4) & 0x07;
  }
  else
  {
    /* restore latched register index */
    index = SN76489.LatchedRegister;
  }

  switch (index)
  {
    case 0:
    case 2:
    case 4: /* Tone Channels frequency */
    {
      if (data & 0x80)
      {
        /* Data byte  %1 cc t dddd */
        SN76489.Registers[index] = (SN76489.Registers[index] & 0x3f0) | (data & 0xf);
      }
      else
      {
        /* Data byte  %0 - dddddd */
        SN76489.Registers[index] = (SN76489.Registers[index] & 0x00f) | ((data & 0x3f) << 4);
      }

      /* zero frequency behaves the same as a value of 1 */
      if (SN76489.Registers[index] == 0)
      {
        SN76489.Registers[index] = 1;
      }
      break;
    }

    case 1:
    case 3:
    case 5: /* Tone Channels attenuation */
    {
      data &= 0x0f;
      SN76489.Registers[index] = data;
      data = PSGVolumeValues[data];
      index >>= 1;
      SN76489.Channel[index][0] = (data * SN76489.PreAmp[index][0]) / 100;
      SN76489.Channel[index][1] = (data * SN76489.PreAmp[index][1]) / 100;
      break;
    }

    case 6: /* Noise control */
    {
      SN76489.Registers[6] = data & 0x0f;

      /* reset shift register */
      SN76489.NoiseShiftRegister = NoiseInitialState;

      /* set noise signal generator frequency */
      SN76489.NoiseFreq = 0x10 << (data&0x3);
      break;
    }

    case 7: /* Noise attenuation */
    {
      data &= 0x0f;
      SN76489.Registers[7] = data;
      data = PSGVolumeValues[data];
      SN76489.Channel[3][0] = (data * SN76489.PreAmp[3][0]) / 100;
      SN76489.Channel[3][1] = (data * SN76489.PreAmp[3][1]) / 100;
      break;
    }
  }
}